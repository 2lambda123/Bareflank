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

#ifndef DISPATCH_FAIL
#define DISPATCH_FAIL

#include <bf_syscall_t.hpp>
#include <gs_t.hpp>
#include <intrinsic_t.hpp>
#include <tls_t.hpp>
#include <vp_pool_t.hpp>
#include <vs_pool_t.hpp>

#include <bsl/debug.hpp>
#include <bsl/discard.hpp>
#include <bsl/errc_type.hpp>
#include <bsl/expects.hpp>
#include <bsl/safe_integral.hpp>

namespace example
{
    /// <!-- description -->
    ///   @brief Dispatches the fail as needed, or returns an error so
    ///     that the microkernel can halt the PP.
    ///
    /// <!-- inputs/outputs -->
    ///   @param gs the gs_t to use
    ///   @param tls the tls_t to use
    ///   @param sys the bf_syscall_t to use
    ///   @param intrinsic the intrinsic_t to use
    ///   @param vp_pool the vp_pool_t to use
    ///   @param vs_pool the vs_pool_t to use
    ///   @param errc the reason for the failure, which is CPU
    ///     specific. On x86, this is a combination of the exception
    ///     vector and error code.
    ///   @param addr contains a faulting address if the fail reason
    ///     is associated with an error that involves a faulting address (
    ///     for example like a page fault). Otherwise, the value of this
    ///     input is undefined.
    ///   @return Returns bsl::errc_success on success, bsl::errc_failure
    ///     and friends otherwise
    ///
    [[nodiscard]] static constexpr auto
    dispatch_fail(
        gs_t const &gs,
        tls_t const &tls,
        syscall::bf_syscall_t const &sys,
        intrinsic_t const &intrinsic,
        vp_pool_t const &vp_pool,
        vs_pool_t const &vs_pool,
        bsl::safe_u64 const &errc,
        bsl::safe_u64 const &addr) noexcept -> bsl::errc_type
    {
        bsl::expects(errc.is_valid_and_checked());
        bsl::expects(addr.is_valid_and_checked());

        bsl::discard(gs);
        bsl::discard(tls);
        bsl::discard(sys);
        bsl::discard(intrinsic);
        bsl::discard(vp_pool);
        bsl::discard(vs_pool);

        /// NOTE:
        /// - Tells the microkernel that we didn't handle the fast fail.
        ///   When this occurs, the microkernel will halt this PP. In most
        ///   cases, there are only two options for how to handle a fail:
        ///   - Do the following, and report an error and halt.
        ///   - Return to a parent VS and continue execution from there,
        ///     which is typically only possible if you are implementing
        ///     more than one VP/VS per PP (e.g., when implementing guest
        ///     support, VSM support or nested virtualization support).
        ///
        /// - Another use case is integration testing. We can also use this
        ///   to generate faults that we can recover from to ensure the
        ///   fault system works properly during testing.
        ///

        bsl::alert() << "this extension does not support handling fast fail events\n";
        return bsl::errc_failure;
    }
}

#endif
