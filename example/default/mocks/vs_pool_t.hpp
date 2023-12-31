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

#ifndef MOCKS_VS_POOL_T_HPP
#define MOCKS_VS_POOL_T_HPP

#include <allocated_status_t.hpp>
#include <bf_syscall_t.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>
#include <tuple>

#include <bsl/discard.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unordered_map.hpp>

namespace example
{
    /// <!-- description -->
    ///   @brief Defines the extension's VS pool
    ///
    class vs_pool_t final
    {
        /// @brief stores the id that will be returned on allocate
        bsl::safe_u16 m_id{};
        /// @brief stores the return value of allocate()
        bsl::unordered_map<std::tuple<bsl::safe_u16, bsl::safe_u16>, bool> m_allocate_fails{};
        /// @brief stores the return value of is_allocated()
        bsl::unordered_map<bsl::safe_u16, allocated_status_t> m_allocated{};
        /// @brief stores the return value of assigned_vp()
        bsl::unordered_map<bsl::safe_u16, bsl::safe_u16> m_assigned_vpid{};
        /// @brief stores the return value of assigned_pp()
        bsl::unordered_map<bsl::safe_u16, bsl::safe_u16> m_assigned_ppid{};

    public:
        /// <!-- description -->
        ///   @brief Initializes this vs_pool_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///
        static constexpr void
        initialize(
            gs_t const &gs,
            tls_t const &tls,
            syscall::bf_syscall_t const &sys,
            intrinsic_t const &intrinsic) noexcept
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(sys);
            bsl::discard(intrinsic);
        }

        /// <!-- description -->
        ///   @brief Allocates a VS and returns it's ID
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vpid the ID of the VM to assign the newly created VS to
        ///   @param ppid the ID of the PP to assign the newly created VS to
        ///   @return Returns ID of the newly allocated vs_t. Returns
        ///     bsl::safe_u16::failure() on failure.
        ///
        [[nodiscard]] constexpr auto
        allocate(
            gs_t const &gs,
            tls_t const &tls,
            syscall::bf_syscall_t const &sys,
            intrinsic_t const &intrinsic,
            bsl::safe_u16 const &vpid,
            bsl::safe_u16 const &ppid) noexcept -> bsl::safe_u16
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(sys);
            bsl::discard(intrinsic);

            if (m_allocate_fails.at({vpid, ppid})) {
                return bsl::safe_u16::failure();
            }

            auto const id{m_id};
            m_id = (m_id + bsl::safe_u16::magic_1()).checked();

            m_assigned_vpid.at(id) = vpid;
            m_assigned_ppid.at(id) = ppid;
            m_allocated.at(id) = allocated_status_t::allocated;

            return id;
        }

        /// <!-- description -->
        ///   @brief Tells the allocate() function to return a failure
        ///     for the provided vpid/ppid combo.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vpid the ID of the VM to assign the newly created VS to
        ///   @param ppid the ID of the PP to assign the newly created VS to
        ///
        constexpr void
        set_allocate_fails(bsl::safe_u16 const &vpid, bsl::safe_u16 const &ppid) noexcept
        {
            m_allocate_fails.at({vpid, ppid}) = true;
        }

        /// <!-- description -->
        ///   @brief Deallocates the requested vs_t
        ///
        /// <!-- inputs/outputs -->
        ///   @param gs the gs_t to use
        ///   @param tls the tls_t to use
        ///   @param sys the bf_syscall_t to use
        ///   @param intrinsic the intrinsic_t to use
        ///   @param vsid the ID of the vs_t to deallocate
        ///
        constexpr void
        deallocate(
            gs_t const &gs,
            tls_t const &tls,
            syscall::bf_syscall_t const &sys,
            intrinsic_t const &intrinsic,
            bsl::safe_u16 const &vsid) noexcept
        {
            bsl::discard(gs);
            bsl::discard(tls);
            bsl::discard(sys);
            bsl::discard(intrinsic);

            bsl::discard(m_assigned_vpid.erase(vsid));
            bsl::discard(m_assigned_ppid.erase(vsid));
            bsl::discard(m_allocated.erase(vsid));
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vs_t is allocated,
        ///     false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @param vsid the ID of the vs_t to query
        ///   @return Returns true if the requested vs_t is allocated,
        ///     false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_allocated(bsl::safe_u16 const &vsid) const noexcept -> bool
        {
            return m_allocated.at(vsid) == allocated_status_t::allocated;
        }

        /// <!-- description -->
        ///   @brief Returns true if the requested vs_t is deallocated,
        ///     false otherwise
        ///
        /// <!-- inputs/outputs -->
        ///   @param vsid the ID of the vs_t to query
        ///   @return Returns true if the requested vs_t is deallocated,
        ///     false otherwise
        ///
        [[nodiscard]] constexpr auto
        is_deallocated(bsl::safe_u16 const &vsid) const noexcept -> bool
        {
            return m_allocated.at(vsid) == allocated_status_t::deallocated;
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the VM the requested vs_t is assigned
        ///     to. If the vs_t is not assigned, syscall::BF_INVALID_ID is
        ///     returned.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vsid the ID of the vs_t to query
        ///   @return Returns the ID of the VM the requested vs_t is assigned
        ///     to. If the vs_t is not assigned, syscall::BF_INVALID_ID is
        ///     returned.
        ///
        [[nodiscard]] constexpr auto
        assigned_vp(bsl::safe_u16 const &vsid) const noexcept -> bsl::safe_u16
        {
            if (!m_assigned_vpid.contains(vsid)) {
                return syscall::BF_INVALID_ID;
            }

            return m_assigned_vpid.at(vsid);
        }

        /// <!-- description -->
        ///   @brief Returns the ID of the PP the requested vs_t is assigned
        ///     to. If the vs_t is not assigned, syscall::BF_INVALID_ID is
        ///     returned.
        ///
        /// <!-- inputs/outputs -->
        ///   @param vsid the ID of the vs_t to query
        ///   @return Returns the ID of the PP the requested vs_t is assigned
        ///     to. If the vs_t is not assigned, syscall::BF_INVALID_ID is
        ///     returned.
        ///
        [[nodiscard]] constexpr auto
        assigned_pp(bsl::safe_u16 const &vsid) const noexcept -> bsl::safe_u16
        {
            if (!m_assigned_ppid.contains(vsid)) {
                return syscall::BF_INVALID_ID;
            }

            return m_assigned_ppid.at(vsid);
        }
    };
}

#endif
