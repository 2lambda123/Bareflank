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

#include <code_aliases_t.h>
#include <platform.h>
#include <types.h>

/**
 * <!-- description -->
 *   @brief Releases a previously allocated code_aliases_t that was allocated
 *     using the alloc_and_copy_mk_code_aliases function.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_a the code_aliases_t to free.
 */
void
free_mk_code_aliases(struct code_aliases_t *const pmut_a) NOEXCEPT
{
    platform_expects(NULLPTR != pmut_a);

    platform_free(pmut_a->demote, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->promote, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->esr_default, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->esr_df, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->esr_gpf, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->esr_nmi, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->esr_pf, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->serial_write_c, HYPERVISOR_PAGE_SIZE);
    platform_free(pmut_a->serial_write_hex, HYPERVISOR_PAGE_SIZE);
    platform_memset(pmut_a, ((uint8_t)0), sizeof(struct code_aliases_t));
}
