/**
 * @copyright
 * Copyright (C) 2020 Assured Information Security, Inc.
 *
 * @copyright
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @copyright
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * @copyright
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cpuid_commands.h>
#include <debug.h>
#include <intrinsic_cpuid.h>
#include <platform.h>
#include <types.h>

/**
 * <!-- description -->
 *   @brief Tells the hypervisor to stop
 *
 * <!-- inputs/outputs -->
 *   @return LOADER_SUCCESS on success, LOADER_FAILURE on failure.
 */
NODISCARD int64_t
send_command_stop(void) NOEXCEPT
{
    uint32_t mut_eax;
    uint32_t mut_ebx;
    uint32_t mut_ecx;
    uint32_t mut_edx;

    mut_eax = CPUID_COMMAND_EAX;
    mut_ecx = CPUID_COMMAND_ECX_STOP;
    platform_mark_gdt_writable();
    intrinsic_cpuid(&mut_eax, &mut_ebx, &mut_ecx, &mut_edx);
    platform_mark_gdt_readonly();

    if (((uint32_t)0) != mut_eax) {
        bferror("stop cpuid command failed");
        return LOADER_FAILURE;
    }

    if (CPUID_COMMAND_ECX_STOP != mut_ecx) {
        bferror("stop cpuid command failed because ecx was not CPUID_COMMAND_ECX_STOP");
        return LOADER_FAILURE;
    }

    return LOADER_SUCCESS;
}
