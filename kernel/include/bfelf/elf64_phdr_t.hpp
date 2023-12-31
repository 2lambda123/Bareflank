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

#ifndef ELF64_PHDR_T_HPP
#define ELF64_PHDR_T_HPP

#include <bsl/convert.hpp>
#include <bsl/cstdint.hpp>

#pragma pack(push, 1)

namespace bfelf
{
    /// @brief defines p_type for unused entry
    constexpr auto PT_NULL{0_u32};
    /// @brief defines p_type for a loadable segment
    constexpr auto PT_LOAD{1_u32};
    /// @brief defines p_type for dynamic linking tables
    constexpr auto PT_DYNAMIC{2_u32};
    /// @brief defines p_type for the program interpreter path
    constexpr auto PT_INTERP{3_u32};
    /// @brief defines p_type for note sections
    constexpr auto PT_NOTE{4_u32};
    /// @brief defines p_type for reserved
    constexpr auto PT_SHLIB{5_u32};
    /// @brief defines p_type for the program header table
    constexpr auto PT_PHDR{6_u32};
    /// @brief defines p_type for the tls segment
    constexpr auto PT_TLS{7_u32};
    /// @brief defines p_type for environment-specific use (lo)
    constexpr auto PT_LOOS{0x60000000_u32};
    /// @brief defines p_type for the GNU stack segment
    constexpr auto PT_GNU_STACK{0x6474e551_u32};
    /// @brief defines p_type for environment-specific use (hi)
    constexpr auto PT_HIOS{0x6FFFFFFF_u32};
    /// @brief defines p_type for processor-specific use (lo)
    constexpr auto PT_LOPROC{0x70000000_u32};
    /// @brief defines p_type for processor-specific use (hi)
    constexpr auto PT_HIPROC{0x7FFFFFFF_u32};

    /// @brief defines p_flags for execute permissions
    constexpr auto PF_X{1_u32};
    /// @brief defines p_flags for write permissions
    constexpr auto PF_W{2_u32};
    /// @brief defines p_flags for read permissions
    constexpr auto PF_R{4_u32};
    /// @brief defines p_flags for environment-specific use
    constexpr auto PF_MASKOS{0x00FF0000_u32};
    /// @brief defines p_flags for environment-specific use
    constexpr auto PF_MASKPROC{0xFF000000_u32};

    /// <!-- description -->
    ///   @brief In executable and shared object files, sections are grouped
    ///     into segments for loading. The program header table contains a
    ///     list of entries describing each segment.
    ///
    struct elf64_phdr_t final
    {
        /// @brief type of segment
        bsl::uint32 p_type;
        /// @brief segment attributes
        bsl::uint32 p_flags;
        /// @brief offset of segment in ELF file
        bsl::uint8 const *p_offset;
        /// @brief virtual address of segment
        bsl::uint64 p_vaddr;
        /// @brief physical address of segment
        bsl::uint64 p_paddr;
        /// @brief size of segment in ELF file
        bsl::uint64 p_filesz;
        /// @brief size of segment in memory
        bsl::uint64 p_memsz;
        /// @brief segment alignment
        bsl::uint64 p_align;
    };
}

#pragma pack(pop)

#endif
