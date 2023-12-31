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

#include <elf_file_t.h>
#include <free_mk_elf_file.h>
#include <platform.h>
#include <types.h>

/**
 * <!-- description -->
 *   @brief Releases a previously allocated elf_file_t that was allocated
 *     using the alloc_and_copy_mk_elf_file function.
 *
 * <!-- inputs/outputs -->
 *   @param pmut_mk_elf_file the elf_file_t to free.
 */
void
free_mk_elf_file(struct elf_file_t *const pmut_mk_elf_file) NOEXCEPT
{
    platform_expects(NULLPTR != pmut_mk_elf_file);

    platform_free(pmut_mk_elf_file->addr, pmut_mk_elf_file->size);
    platform_memset(pmut_mk_elf_file, ((uint8_t)0), sizeof(struct elf_file_t));
}
