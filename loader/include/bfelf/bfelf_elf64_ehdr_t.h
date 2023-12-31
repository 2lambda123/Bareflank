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

#ifndef BFELF_ELF64_EHDR_T_H
#define BFELF_ELF64_EHDR_T_H

#include "bfelf_elf64_phdr_t.h"
#include "bfelf_elf64_shdr_t.h"

#include <debug.h>
#include <platform.h>
#include <types.h>

#ifdef __cplusplus
extern "C"
{
#endif

#pragma pack(push, 1)

/** @brief e_ident[bfelf_ei_mag0] contains 0x7FU for file identification */
#define bfelf_ei_mag0 ((uint64_t)0U)
/** @brief e_ident[bfelf_ei_mag1] contains 0x45U for file identification */
#define bfelf_ei_mag1 ((uint64_t)1U)
/** @brief e_ident[bfelf_ei_mag2] contains 0x4CU for file identification */
#define bfelf_ei_mag2 ((uint64_t)2U)
/** @brief e_ident[bfelf_ei_mag3] contains 0x46U for file identification */
#define bfelf_ei_mag3 ((uint64_t)3U)
/** @brief e_ident[bfelf_ei_class] identifies if the file is 32bit or 64 bit */
#define bfelf_ei_class ((uint64_t)4U)
/** @brief e_ident[bfelf_ei_data] specifies the data bit encoding of the file */
#define bfelf_ei_data ((uint64_t)5U)
/** @brief e_ident[bfelf_ei_version] identifies the version of the file */
#define bfelf_ei_version ((uint64_t)6U)
/** @brief e_ident[bfelf_ei_osabi] identifies file's ABI scheme */
#define bfelf_ei_osabi ((uint64_t)7U)
/** @brief e_ident[bfelf_ei_abiversion] identifies file's ABI version */
#define bfelf_ei_abiversion ((uint64_t)8U)
/** @brief defines the size of e_ident */
#define bfelf_ei_nident ((uint64_t)16U)

/** @brief defines the expected e_ident[bfelf_ei_mag0] value */
#define bfelf_elfmag0 ((uint8_t)0x7FU)
/** @brief defines the expected e_ident[bfelf_ei_mag1] value */
#define bfelf_elfmag1 ((uint8_t)0x45U)
/** @brief defines the expected e_ident[bfelf_ei_mag2] value */
#define bfelf_elfmag2 ((uint8_t)0x4CU)
/** @brief defines the expected e_ident[bfelf_ei_mag3] value */
#define bfelf_elfmag3 ((uint8_t)0x46U)

/** @brief defines e_ident[bfelf_ei_class] for 32bit objects */
#define bfelf_elfclass32 ((uint8_t)1U)
/** @brief defines e_ident[bfelf_ei_class] for 64bit objects */
#define bfelf_elfclass64 ((uint8_t)2U)

/** @brief defines e_ident[bfelf_ei_data] for little endian */
#define bfelf_elfdata2lsb ((uint8_t)1U)
/** @brief defines e_ident[bfelf_ei_data] for big endian */
#define bfelf_elfdata2msb ((uint8_t)2U)

/** @brief defines e_ident[bfelf_ei_osabi] for system v abi */
#define bfelf_elfosabi_sysv ((uint8_t)0U)
/** @brief defines e_ident[bfelf_ei_osabi] for hp-ux operating system */
#define bfelf_elfosabi_hpux ((uint8_t)1U)
/** @brief defines e_ident[bfelf_ei_osabi] for standalone applications */
#define bfelf_elfosabi_standalone ((uint8_t)255U)

/** @brief defines e_type for no file type */
#define bfelf_et_none ((uint16_t)0U)
/** @brief defines e_type for an relocatable object file */
#define bfelf_et_rel ((uint16_t)1U)
/** @brief defines e_type for an executable file */
#define bfelf_et_exec ((uint16_t)2U)
/** @brief defines e_type for an shared object file */
#define bfelf_et_dyn ((uint16_t)3U)
/** @brief defines e_type for an core file */
#define bfelf_et_core ((uint16_t)4U)
/** @brief defines e_type for an environment-specific use (lo) */
#define bfelf_et_loos ((uint16_t)0xFE00U)
/** @brief defines e_type for an environment-specific use (hi) */
#define bfelf_et_hios ((uint16_t)0xFEFFU)
/** @brief defines e_type for an processor-specific use (lo) */
#define bfelf_et_loproc ((uint16_t)0xFF00U)
/** @brief defines e_type for an processor-specific use (hi) */
#define bfelf_et_hiproc ((uint16_t)0xFFFFU)

    /**
     * <!-- description -->
     *   @brief The file header is located at the beginning of the file,
     *     and is used to locate the other parts of the file
     */
    struct bfelf_elf64_ehdr_t
    {
        /** @brief ELF identification */
        uint8_t e_ident[bfelf_ei_nident];
        /** @brief Object file type */
        uint16_t e_type;
        /** @brief Machine type */
        uint16_t e_machine;
        /** @brief Object file version */
        uint32_t e_version;
        /** @brief Entry point address */
        uint64_t e_entry;
        /** @brief Pointer to program header */
        struct bfelf_elf64_phdr_t *e_phdr;
        /** @brief Pointer to section header */
        struct bfelf_elf64_shdr_t *e_shdr;
        /** @brief Processor-specific flags */
        uint32_t e_flags;
        /** @brief ELF header size */
        uint16_t e_ehsize;
        /** @brief Size of program header entry */
        uint16_t e_phentsize;
        /** @brief Number of program header entries */
        uint16_t e_phnum;
        /** @brief Size of section header entry */
        uint16_t e_shentsize;
        /** @brief Number of section header entries */
        uint16_t e_shnum;
        /** @brief Section name string table index */
        uint16_t e_shstrndx;
    };

    /**
     * <!-- description -->
     *   @brief Checks whether or not a given ELF file is in a format that
     *     this ELF loader can handle.
     *
     * <!-- inputs/outputs -->
     *   @param ehdr a pointer to the ELF file
     *   @return Returns 0 on success or an error code on failure.
     */
    NODISCARD static inline int64_t
    validate_elf64_ehdr(struct bfelf_elf64_ehdr_t const *const ehdr) NOEXCEPT
    {
        platform_expects(NULLPTR != ehdr);

        if ((int32_t)bfelf_elfmag0 != (int32_t)ehdr->e_ident[bfelf_ei_mag0]) {
            bferror_x8("invalid bfelf_ei_mag0", ehdr->e_ident[bfelf_ei_mag0]);
            return LOADER_FAILURE;
        }

        if ((int32_t)bfelf_elfmag1 != (int32_t)ehdr->e_ident[bfelf_ei_mag1]) {
            bferror_x8("invalid bfelf_ei_mag1", ehdr->e_ident[bfelf_ei_mag1]);
            return LOADER_FAILURE;
        }

        if ((int32_t)bfelf_elfmag2 != (int32_t)ehdr->e_ident[bfelf_ei_mag2]) {
            bferror_x8("invalid bfelf_ei_mag2", ehdr->e_ident[bfelf_ei_mag2]);
            return LOADER_FAILURE;
        }

        if ((int32_t)bfelf_elfmag3 != (int32_t)ehdr->e_ident[bfelf_ei_mag3]) {
            bferror_x8("invalid bfelf_ei_mag3", ehdr->e_ident[bfelf_ei_mag3]);
            return LOADER_FAILURE;
        }

        if ((int32_t)bfelf_elfclass64 != (int32_t)ehdr->e_ident[bfelf_ei_class]) {
            bferror_x8("invalid bfelf_ei_class", ehdr->e_ident[bfelf_ei_class]);
            return LOADER_FAILURE;
        }

        if ((int32_t)bfelf_elfosabi_sysv != (int32_t)ehdr->e_ident[bfelf_ei_osabi]) {
            bferror_x8("invalid bfelf_ei_osabi", ehdr->e_ident[bfelf_ei_osabi]);
            return LOADER_FAILURE;
        }

        if ((int32_t)bfelf_et_exec != (int32_t)ehdr->e_type) {
            bferror_x16("invalid e_type", ehdr->e_type);
            return LOADER_FAILURE;
        }

        return LOADER_SUCCESS;
    }

    /**
     * <!-- description -->
     *   @brief The program and section header locations in ELF are actually
     *     offsets, not pointers. The problem is, this requires arithmetic that
     *     is not allowed, especially in C++. To avoid this, our version of
     *     the ELF header uses pointers in the ELF file. This function performs
     *     the arithmetic and conversion so that the rest of the code can simply
     *     use the pointers as is. Meaning, if we have to commit a sin, lets do
     *     it in one place where it is easy to test. All other code will be type
     *     safe and compliant.
     *
     * <!-- inputs/outputs -->
     *   @param pmut_ehdr a pointer to the ELF file
     */
    static inline void
    update_elf64_ehdr(struct bfelf_elf64_ehdr_t *const pmut_ehdr) NOEXCEPT
    {
        uint64_t mut_i;
        uint64_t mut_start;
        uint64_t mut_phoff;
        uint64_t mut_shoff;

        platform_expects(NULLPTR != pmut_ehdr);

        mut_start = ((uint64_t)pmut_ehdr);
        mut_phoff = ((uint64_t)pmut_ehdr->e_phdr);
        mut_shoff = ((uint64_t)pmut_ehdr->e_shdr);

        pmut_ehdr->e_phdr = ((struct bfelf_elf64_phdr_t *)(mut_phoff + mut_start));
        pmut_ehdr->e_shdr = ((struct bfelf_elf64_shdr_t *)(mut_shoff + mut_start));

        for (mut_i = ((uint64_t)0); mut_i < (uint64_t)pmut_ehdr->e_phnum; ++mut_i) {
            uint64_t const off = ((uint64_t)pmut_ehdr->e_phdr[mut_i].p_offset);
            pmut_ehdr->e_phdr[mut_i].p_offset = ((uint8_t *)(off + mut_start));
        }

        for (mut_i = ((uint64_t)0); mut_i < (uint64_t)pmut_ehdr->e_shnum; ++mut_i) {
            uint64_t const off = ((uint64_t)pmut_ehdr->e_shdr[mut_i].sh_offset);
            pmut_ehdr->e_shdr[mut_i].sh_offset = ((uint8_t *)(off + mut_start));
        }
    }

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif
