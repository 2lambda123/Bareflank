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

#include <ioctl_t.hpp>
#include <loader_platform_interface.hpp>
#include <vmmctl_main.hpp>

#include <bsl/arguments.hpp>
#include <bsl/basic_errc_type.hpp>
#include <bsl/convert.hpp>
#include <bsl/cstdint.hpp>
#include <bsl/cstr_type.hpp>
#include <bsl/enable_color.hpp>
#include <bsl/exit_code.hpp>
#include <bsl/unlikely.hpp>

/// <!-- description -->
///   @brief Provides the main entry point for this application.
///
/// <!-- inputs/outputs -->
///   @param argc the total number of arguments provided to the application
///   @param argv the arguments provided to the application
///   @return bsl::exit_success on success, bsl::exit_failure otherwise.
///
[[nodiscard]] auto
VMMCTL_MAIN(bsl::int32 const argc, bsl::cstr_type const *const argv) noexcept    // NOLINT
    -> bsl::exit_code
{
    bsl::enable_color();

    bsl::arguments mut_args{bsl::to_umx(argc), argv};
    ++mut_args;

    vmmctl::ioctl_t mut_ioctl{loader::DEVICE_NAME};
    if (bsl::unlikely(!mut_ioctl.is_open())) {    // GRCOV_EXCLUDE_BR
        return bsl::exit_failure;                 // GRCOV_EXCLUDE
    }

    vmmctl::vmmctl_main mut_app{};
    auto const ret{mut_app.process(mut_args, mut_ioctl)};
    if (bsl::unlikely(!ret)) {
        return bsl::exit_failure;
    }

    return bsl::exit_success;
}
