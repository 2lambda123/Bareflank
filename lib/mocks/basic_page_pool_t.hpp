/// @copyright
/// Copyright (C) 2020 Assured Information Security, Inc.
///
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// @copyright
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#ifndef MOCK_BASIC_PAGE_POOL_T_HPP
#define MOCK_BASIC_PAGE_POOL_T_HPP

#if __has_include("page_pool_helpers.hpp")
#include <page_pool_helpers.hpp>    // IWYU pragma: export
#endif

#if __has_include("basic_page_pool_helpers.hpp")
#include <basic_page_pool_helpers.hpp>    // IWYU pragma: export
#endif

// IWYU pragma: no_include "page_pool_helpers.hpp"
// IWYU pragma: no_include "basic_page_pool_helpers.hpp"

#include <basic_page_pool_node_t.hpp>

#include <bsl/discard.hpp>
#include <bsl/dontcare_t.hpp>
#include <bsl/expects.hpp>
#include <bsl/is_pod.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/span.hpp>
#include <bsl/touch.hpp>
#include <bsl/unordered_map.hpp>

namespace lib
{
    /// <!-- description -->
    ///   @brief the basic_page_pool_t is responsible for allocating and freeing
    ///      pages. The loader provides a linked list with the pages that
    ///      this code will allocate as requested. Each page exists in the
    ///      direct map, so all virt to phys translations of allocated pages
    ///      can be done using simple arithmetic.
    ///
    /// <!-- template parameters -->
    ///   @tparam TLS_TYPE the type of TLS block to use
    ///   @tparam SYS_TYPE the type of bf_syscall_t to use
    ///
    template<typename TLS_TYPE, typename SYS_TYPE = bsl::dontcare_t>
    class basic_page_pool_t final
    {
        /// @brief store the max number of allocations
        bsl::safe_umx m_max{};
        /// @brief store whether or not a max value is enabled.
        bool m_enable_max{};
        /// @brief stores the total number of bytes given to the basic_page_pool_t.
        bsl::safe_umx m_size{};
        /// @brief stores the total number of bytes given to the basic_page_pool_t.
        bsl::safe_umx m_used{};
        /// @brief store the virt to phys translations
        bsl::unordered_map<void const *, bsl::safe_u64> m_virt_to_phys{};
        /// @brief store the virt to phys translations
        bsl::unordered_map<bsl::safe_u64, helpers::page_pool_storage_t> m_phys_to_virt{};
        /// @brief store a single virtual address based on type
        helpers::page_pool_storage_t m_allocate{};

        /// <!-- description -->
        ///   @brief Returns the number of bytes allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the number of bytes allocated.
        ///
        [[nodiscard]] constexpr auto
        allocated() const noexcept -> bsl::safe_umx
        {
            /// NOTE:
            /// - The following is marked checked because the allocation
            ///   function ensures this math will never overflow.
            ///

            return m_used.checked();
        }

        /// <!-- description -->
        ///   @brief Returns this->size() - this->allocated().
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns this->size() - this->allocated().
        ///
        [[nodiscard]] constexpr auto
        remaining() const noexcept -> bsl::safe_umx
        {
            /// NOTE:
            /// - The following is marked checked because the allocation
            ///   function ensures this math will never overflow.
            ///

            return (this->size() - this->allocated()).checked();
        }

    public:
        /// <!-- description -->
        ///   @brief Creates the basic_page_pool_t given a mutable_buffer_t to
        ///     the basic_page_pool_t as well as the virtual address base of the
        ///     page pool which is used for virt to phys translations.
        ///
        /// <!-- inputs/outputs -->
        ///   @param pool the mutable_buffer_t of the basic_page_pool_t
        ///
        static constexpr void
        initialize(bsl::span<basic_page_pool_node_t> const &pool) noexcept
        {
            bsl::discard(pool);
        }

        /// <!-- description -->
        ///   @brief Allocates a page from the basic_page_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to allocate
        ///   @param tls the current TLS block
        ///   @return Returns a pointer to the newly allocated page
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        allocate(TLS_TYPE const &tls) noexcept -> T *
        {
            return this->allocate<T>(tls, bsl::dontcare);
        }

        /// <!-- description -->
        ///   @brief Allocates a page from the basic_page_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to allocate
        ///   @param tls the current TLS block
        ///   @param sys the bf_syscall_t to use
        ///   @return Returns a pointer to the newly allocated page
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        allocate(TLS_TYPE const &tls, SYS_TYPE const &sys) noexcept -> T *
        {
            T *pmut_mut_virt{};
            bsl::safe_u64 mut_phys{};

            static_assert(bsl::is_pod<T>::value);
            static_assert(sizeof(T) == HYPERVISOR_PAGE_SIZE);

            bsl::discard(tls);
            bsl::discard(sys);

            m_size += HYPERVISOR_PAGE_SIZE;
            m_used += HYPERVISOR_PAGE_SIZE;

            if (m_enable_max) {
                if (m_max.is_zero()) {
                    return nullptr;
                }

                m_max = (--m_max).checked();
            }
            else {
                bsl::touch();
            }

            if (helpers::is_page_pool_storage_set<T>(m_allocate)) {
                pmut_mut_virt = helpers::get_virt<T>(m_allocate);
                mut_phys = helpers::get_phys<T>(m_allocate);
            }
            else {
                // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
                pmut_mut_virt = new T();
                mut_phys = m_size.checked();
            }

            m_virt_to_phys.at(pmut_mut_virt) = mut_phys;
            helpers::set_page_pool_storage<T>(m_phys_to_virt.at(mut_phys), pmut_mut_virt, mut_phys);

            return pmut_mut_virt;
        }

        /// <!-- description -->
        ///   @brief Sets the results of allocate for a specific type
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to set
        ///   @param pmut_virt the virtual address of the pointer to set
        ///   @param phys the physical address of the pointer to set
        ///
        template<typename T>
        constexpr void
        set_allocate(T *const pmut_virt, bsl::safe_u64 const &phys) noexcept
        {
            static_assert(bsl::is_pod<T>::value);
            static_assert(sizeof(T) == HYPERVISOR_PAGE_SIZE);

            helpers::set_page_pool_storage(m_allocate, pmut_virt, phys);
        }

        /// <!-- description -->
        ///   @brief Sets the max number of allocations before the allocator
        ///     will return a nullptr as if it were out of memory.
        ///
        /// <!-- inputs/outputs -->
        ///   @param max the max number of supported allocations
        ///
        constexpr void
        set_max(bsl::safe_umx const &max) noexcept
        {
            bsl::expects(max.is_valid_and_checked());
            m_max = max;
            m_enable_max = true;
        }

        /// <!-- description -->
        ///   @brief Returns a page previously allocated using the allocate
        ///     function to the basic_page_pool_t.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T the type of pointer to deallocate
        ///   @param tls the current TLS block
        ///   @param virt the pointer to the page to deallocate
        ///
        template<typename T>
        constexpr void
        deallocate(TLS_TYPE const &tls, T const *const virt) noexcept
        {
            static_assert(bsl::is_pod<T>::value);
            static_assert(sizeof(T) == HYPERVISOR_PAGE_SIZE);

            bsl::discard(tls);
            bsl::expects(nullptr != virt);

            auto const phys{this->virt_to_phys(virt)};
            m_used -= HYPERVISOR_PAGE_SIZE;

            if (helpers::is_page_pool_storage_set<T>(m_allocate)) {
                helpers::set_page_pool_storage<T>(m_allocate, {}, {});
            }
            else {
                // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
                delete virt;    // GRCOV_EXCLUDE_BR
            }

            m_virt_to_phys.at(virt) = {};
            m_phys_to_virt.at(phys) = {};
        }

        /// <!-- description -->
        ///   @brief Returns the number of bytes in the pool.
        ///
        /// <!-- inputs/outputs -->
        ///   @return Returns the number of bytes in the pool.
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> bsl::safe_umx
        {
            return m_size.checked();
        }

        /// <!-- description -->
        ///   @brief Returns the number of bytes allocated.
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @return Returns the number of bytes allocated.
        ///
        [[nodiscard]] constexpr auto
        allocated(TLS_TYPE const &tls) const noexcept -> bsl::safe_umx
        {
            bsl::discard(tls);
            return this->allocated();
        }

        /// <!-- description -->
        ///   @brief Returns this->size() - this->allocated().
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///   @return Returns this->size() - this->allocated().
        ///
        [[nodiscard]] constexpr auto
        remaining(TLS_TYPE const &tls) const noexcept -> bsl::safe_umx
        {
            bsl::discard(tls);
            return this->remaining();
        }

        /// <!-- description -->
        ///   @brief Converts a virtual address to a physical address.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T defines the type of virtual address being converted
        ///   @param virt the virtual address to convert
        ///   @return the resulting physical address
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        virt_to_phys(T const *const virt) const noexcept -> bsl::safe_umx
        {
            static_assert(bsl::is_pod<T>::value);
            static_assert(sizeof(T) == HYPERVISOR_PAGE_SIZE);

            bsl::expects(nullptr != virt);
            bsl::expects(m_virt_to_phys.contains(virt));

            return m_virt_to_phys.at(virt);
        }

        /// <!-- description -->
        ///   @brief Converts a physical address to a virtual address.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam T defines the type of virtual address to convert to
        ///   @param phys the physical address to convert
        ///   @return the resulting virtual address
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        phys_to_virt(bsl::safe_u64 const &phys) const noexcept -> T *
        {
            static_assert(bsl::is_pod<T>::value);
            static_assert(sizeof(T) == HYPERVISOR_PAGE_SIZE);

            bsl::expects(phys.is_valid_and_checked());
            bsl::expects(phys.is_pos());
            bsl::expects(m_phys_to_virt.contains(phys));

            return helpers::get_virt<T>(m_phys_to_virt.at(phys));
        }

        /// <!-- description -->
        ///   @brief Dumps the basic_page_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param tls the current TLS block
        ///
        constexpr void
        dump(TLS_TYPE const &tls) const noexcept
        {
            bsl::discard(tls);
        }
    };
}

#endif
