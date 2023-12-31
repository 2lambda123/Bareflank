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

#include "../../../mocks/basic_ifmap_t.hpp"

#include <bsl/convert.hpp>
#include <bsl/safe_integral.hpp>
#include <bsl/span.hpp>
#include <bsl/ut.hpp>

namespace lib
{
    /// <!-- description -->
    ///   @brief Used to execute the actual checks. We put the checks in this
    ///     function so that we can validate the tests both at compile-time
    ///     and at run-time. If a bsl::ut_check fails, the tests will either
    ///     fail fast at run-time, or will produce a compile-time error.
    ///
    /// <!-- inputs/outputs -->
    ///   @return Always returns bsl::exit_success.
    ///
    [[nodiscard]] constexpr auto
    tests() noexcept -> bsl::exit_code
    {
        bsl::ut_scenario{"success"} = []() noexcept {
            bsl::ut_given{} = []() noexcept {
                basic_ifmap_t mut_ifmap{"success"};
                constexpr auto gpa{0x1000_u64};
                bsl::ut_then{} = [&]() noexcept {
                    bsl::ut_check(mut_ifmap.view().is_valid());
                    bsl::ut_check(nullptr != mut_ifmap.data());
                    bsl::ut_check(!mut_ifmap.empty());
                    bsl::ut_check(!!mut_ifmap);
                    bsl::ut_check(mut_ifmap.size().is_pos());
                    mut_ifmap.set_gpa(gpa);
                    bsl::ut_check(gpa == mut_ifmap.gpa());
                };
                bsl::ut_cleanup{} = [&]() noexcept {
                    mut_ifmap.release();
                };
            };
        };

        bsl::ut_scenario{"failure"} = []() noexcept {
            bsl::ut_given{} = []() noexcept {
                basic_ifmap_t mut_ifmap{"failure"};
                constexpr auto gpa{0x1000_u64};
                bsl::ut_then{} = [&]() noexcept {
                    bsl::ut_check(mut_ifmap.view().is_invalid());
                    bsl::ut_check(nullptr == mut_ifmap.data());
                    bsl::ut_check(mut_ifmap.empty());
                    bsl::ut_check(!mut_ifmap);
                    bsl::ut_check(mut_ifmap.size().is_zero());
                    mut_ifmap.set_gpa(gpa);
                    bsl::ut_check(gpa == mut_ifmap.gpa());
                };
                bsl::ut_cleanup{} = [&]() noexcept {
                    mut_ifmap.release();
                };
            };
        };

        return bsl::ut_success();
    }
}

/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> bsl::exit_code
{
    bsl::enable_color();

    static_assert(lib::tests() == bsl::ut_success());
    return lib::tests();
}
