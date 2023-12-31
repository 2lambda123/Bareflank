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

#ifndef GET_GDT_DESCRIPTOR_ATTRIB_H
#define GET_GDT_DESCRIPTOR_ATTRIB_H

#include <global_descriptor_table_register_t.h>
#include <types.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * <!-- description -->
     *   @brief Sets a GDT descriptor's attrib given a GDT and a selector into
     *     the provided GDT.
     *
     * <!-- inputs/outputs -->
     *   @param gdtr a pointer to the gdtr that stores the GDT to get from
     *   @param selector the selector of the descriptor in the provided GDT
     *     to get from
     *   @param pmut_attrib a pointer to store the the resulting attrib to
     */
    void get_gdt_descriptor_attrib(
        struct global_descriptor_table_register_t const *const gdtr,
        uint16_t const selector,
        uint16_t *const pmut_attrib) NOEXCEPT;

#ifdef __cplusplus
}
#endif

#endif
