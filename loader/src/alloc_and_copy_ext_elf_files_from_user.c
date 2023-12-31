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

#include <alloc_and_copy_ext_elf_files_from_user.h>
#include <bfelf/bfelf_elf64_ehdr_t.h>
#include <debug.h>
#include <elf_file_t.h>
#include <free_ext_elf_files.h>
#include <platform.h>
#include <span_t.h>
#include <types.h>

/**
 * <!-- description -->
 *   @brief This function provides the guts of the
 *     alloc_and_copy_ext_elf_files_from_user function, by performing the
 *     allocation and copy operation for a single elf file.
 *
 * <!-- inputs/outputs -->
 *   @param ext_elf_file_from_user the ELF file to copy
 *   @param pmut_copied_ext_elf_file where to copy the ELF file too
 *   @return LOADER_SUCCESS on success, LOADER_FAILURE on failure.
 */
NODISCARD static int64_t
alloc_and_copy_ext_elf_file_from_user(
    struct span_t const *const ext_elf_file_from_user,
    struct elf_file_t *const pmut_copied_ext_elf_file) NOEXCEPT
{
    uint8_t const *const src_addr = ext_elf_file_from_user->addr;
    uint64_t const dst_size = ext_elf_file_from_user->size;

    struct bfelf_elf64_ehdr_t *const pmut_dst_addr =
        (struct bfelf_elf64_ehdr_t *)platform_alloc(dst_size);
    if (NULLPTR == pmut_dst_addr) {
        bferror("platform_alloc failed");
        goto platform_alloc_failed;
    }

    if (platform_copy_from_user(pmut_dst_addr, src_addr, dst_size)) {
        bferror("platform_copy_from_user failed");
        goto platform_copy_from_user_failed;
    }

    update_elf64_ehdr(pmut_dst_addr);
    pmut_copied_ext_elf_file->addr = pmut_dst_addr;
    pmut_copied_ext_elf_file->size = dst_size;

    return LOADER_SUCCESS;

platform_copy_from_user_failed:

    platform_free(pmut_dst_addr, dst_size);
platform_alloc_failed:

    pmut_copied_ext_elf_file->addr = NULLPTR;
    pmut_copied_ext_elf_file->size = ((uint64_t)0);
    return LOADER_FAILURE;
}

/**
 * <!-- description -->
 *   @brief When the start VMM function is executed, the user must provide
 *     the address and size of the extension ELF files to be loaded and
 *     executed. This ELF files exist in user-space memory and cannot be
 *     directly accessed. As a result, we must copy the arrays from user
 *     space into arrays in the kernel where the loader exists. This
 *     function performs this copy by first allocating arrays the size
 *     of the ELF files being copied and then copies the contents to these
 *     newly allocated arrays. For this reason, once this ELF files are no
 *     longer needed, you must free the ELF files as memory was previously
 *     allocated.
 *
 * <!-- inputs/outputs -->
 *   @param ext_elf_files_from_user the ELF files to copy
 *   @param pmut_copied_ext_elf_files where to copy the ELF files too
 *   @return LOADER_SUCCESS on success, LOADER_FAILURE on failure.
 */
NODISCARD int64_t
alloc_and_copy_ext_elf_files_from_user(
    struct span_t const *const ext_elf_files_from_user,
    struct elf_file_t *const pmut_copied_ext_elf_files) NOEXCEPT
{
    uint64_t mut_i;

    for (mut_i = ((uint64_t)0); mut_i < HYPERVISOR_MAX_EXTENSIONS; ++mut_i) {
        struct span_t const *const src = &ext_elf_files_from_user[mut_i];
        struct elf_file_t *const pmut_dst = &pmut_copied_ext_elf_files[mut_i];

        if (NULLPTR == src->addr) {
            pmut_copied_ext_elf_files[mut_i].addr = NULLPTR;
            pmut_copied_ext_elf_files[mut_i].size = ((uint64_t)0);
            continue;
        }

        if (alloc_and_copy_ext_elf_file_from_user(src, pmut_dst)) {
            bferror("platform_copy_from_user failed");
            goto alloc_and_copy_ext_elf_file_from_user_failed;
        }

        bf_touch();
    }

    return LOADER_SUCCESS;

alloc_and_copy_ext_elf_file_from_user_failed:

    free_ext_elf_files(pmut_copied_ext_elf_files);
    return LOADER_FAILURE;
}
