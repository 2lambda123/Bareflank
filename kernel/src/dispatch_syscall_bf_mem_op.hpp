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

#ifndef DISPATCH_SYSCALL_BF_MEM_OP_HPP
#define DISPATCH_SYSCALL_BF_MEM_OP_HPP

#include "dispatch_syscall_helpers.hpp"

#include <basic_alloc_huge_t.hpp>
#include <basic_alloc_page_t.hpp>
#include <bf_constants.hpp>
#include <bf_types.hpp>
#include <ext_t.hpp>
#include <huge_pool_t.hpp>
#include <page_pool_t.hpp>
#include <tls_t.hpp>

#include <bsl/debug.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/unlikely.hpp>

namespace mk
{
    /// <!-- description -->
    ///   @brief Implements the bf_mem_op_alloc_page syscall
    ///
    /// <!-- inputs/outputs -->
    ///   @param mut_tls the current TLS block
    ///   @param mut_page_pool the page_pool_t to use
    ///   @return Returns a bf_status_t containing success or failure
    ///
    [[nodiscard]] constexpr auto
    syscall_bf_mem_op_alloc_page(tls_t &mut_tls, page_pool_t &mut_page_pool) noexcept
        -> syscall::bf_status_t
    {
        auto const page{mut_tls.ext->alloc_page(mut_tls, mut_page_pool)};
        if (bsl::unlikely(page.virt.is_invalid())) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        mut_tls.ext_reg0 = page.virt.get();
        mut_tls.ext_reg1 = page.phys.get();

        return syscall::BF_STATUS_SUCCESS;
    }

    /// <!-- description -->
    ///   @brief Implements the bf_mem_op_alloc_huge syscall
    ///
    /// <!-- inputs/outputs -->
    ///   @param mut_tls the current TLS block
    ///   @param mut_page_pool the page_pool_t to use
    ///   @param mut_huge_pool the huge pool to use
    ///   @return Returns a bf_status_t containing success or failure
    ///
    [[nodiscard]] constexpr auto
    syscall_bf_mem_op_alloc_huge(
        tls_t &mut_tls, page_pool_t &mut_page_pool, huge_pool_t &mut_huge_pool) noexcept
        -> syscall::bf_status_t
    {
        auto const size{get_huge_size(mut_tls.ext_reg1)};
        if (bsl::unlikely(size.is_invalid())) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_INVALID_INPUT_REG1;
        }

        auto const huge{mut_tls.ext->alloc_huge(mut_tls, mut_page_pool, mut_huge_pool, size)};
        if (bsl::unlikely(huge.virt.is_invalid())) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_UNKNOWN;
        }

        mut_tls.ext_reg0 = huge.virt.get();
        mut_tls.ext_reg1 = huge.phys.get();

        return syscall::BF_STATUS_SUCCESS;
    }

    /// <!-- description -->
    ///   @brief Dispatches the bf_mem_op syscalls
    ///
    /// <!-- inputs/outputs -->
    ///   @param mut_tls the current TLS block
    ///   @param mut_page_pool the page_pool_t to use
    ///   @param mut_huge_pool the huge pool to use
    ///   @return Returns a bf_status_t containing success or failure
    ///
    [[nodiscard]] constexpr auto
    dispatch_syscall_bf_mem_op(
        tls_t &mut_tls, page_pool_t &mut_page_pool, huge_pool_t &mut_huge_pool) noexcept
        -> syscall::bf_status_t
    {
        if (bsl::unlikely(!verify_handle_for_current_ext(mut_tls))) {
            bsl::print<bsl::V>() << bsl::here();
            return syscall::BF_STATUS_FAILURE_INVALID_HANDLE;
        }

        switch (syscall::bf_syscall_index(mut_tls.ext_syscall).get()) {
            case syscall::BF_MEM_OP_ALLOC_PAGE_IDX_VAL.get(): {
                auto const ret{syscall_bf_mem_op_alloc_page(mut_tls, mut_page_pool)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            case syscall::BF_MEM_OP_ALLOC_HUGE_IDX_VAL.get(): {
                auto const ret{syscall_bf_mem_op_alloc_huge(mut_tls, mut_page_pool, mut_huge_pool)};
                if (bsl::unlikely(ret != syscall::BF_STATUS_SUCCESS)) {
                    bsl::print<bsl::V>() << bsl::here();
                    return ret;
                }

                return ret;
            }

            default: {
                break;
            }
        }

        return report_syscall_unknown_unsupported(mut_tls);
    }
}

#endif
