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

#ifndef BSL_CSTDIO_HPP
#define BSL_CSTDIO_HPP

#include <bsl/char_type.hpp>
#include <bsl/cstdint.hpp>
#include <bsl/cstr_type.hpp>
#include <bsl/is_constant_evaluated.hpp>

namespace syscall
{
    /// NOTE:
    /// - We provide these prototypes ourselves instead of including
    ///   the header files because the debugging portion of the runtime
    ///   for both the microkernel, and for extensions provides the
    ///   foundation for everything, including asserts. These are needed
    ///   to implement even the basics for safe integrals, so you end up
    ///   with circular dependencies.
    ///
    /// - The impl prototypes also do not bring these headers in, but the
    ///   mocks do, because they really need to provide the mocked version
    ///   of this code, and having access to more of the BSL helps with
    ///   that, so providing the prototypes here ensures that there are
    ///   no issues no matter what happens.
    ///

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_write_c.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///
    extern "C" void bf_debug_op_write_c_impl(bsl::char_type const reg0_in) noexcept;    // NOLINT

    /// <!-- description -->
    ///   @brief Implements the ABI for bf_debug_op_write_str.
    ///
    /// <!-- inputs/outputs -->
    ///   @param reg0_in n/a
    ///   @param reg1_in n/a
    ///
    extern "C" void bf_debug_op_write_str_impl(    // NOLINT
        bsl::char_type const *const reg0_in,
        bsl::uintmx const reg1_in) noexcept;
}

namespace bsl
{
    /// <!-- description -->
    ///   @brief Output a character to stdout
    ///
    /// <!-- inputs/outputs -->
    ///   @param c the character to output
    ///
    constexpr void
    stdio_out_char(bsl::char_type const c) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        syscall::bf_debug_op_write_c_impl(c);
    }

    /// <!-- description -->
    ///   @brief Output a string to stdout
    ///
    /// <!-- inputs/outputs -->
    ///   @param str the string to output
    ///   @param len the total number of bytes to output
    ///
    constexpr void
    stdio_out_cstr(bsl::cstr_type const str, bsl::uintmx const len) noexcept
    {
        if (bsl::is_constant_evaluated()) {
            return;
        }

        syscall::bf_debug_op_write_str_impl(str, len);
    }
}

#endif
