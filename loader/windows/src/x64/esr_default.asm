; @copyright
; Copyright (C) 2020 Assured Information Security, Inc.
;
; @copyright
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; @copyright
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; @copyright
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.

    serial_write_c PROTO

    esr_default_text SEGMENT ALIGN(1000h) 'CODE'
    esr_default PROC

    mov rcx, 'e'
    call serial_write_c

    mov rcx, 's'
    call serial_write_c

    mov rcx, 'r'
    call serial_write_c

    mov rcx, '_'
    call serial_write_c

    mov rcx, 'd'
    call serial_write_c

    mov rcx, 'e'
    call serial_write_c

    mov rcx, 'f'
    call serial_write_c

    mov rcx, 'a'
    call serial_write_c

    mov rcx, 'u'
    call serial_write_c

    mov rcx, 'l'
    call serial_write_c

    mov rcx, 't'
    call serial_write_c

    mov rcx, '\n'
    call serial_write_c

    cli
    hlt

    esr_default ENDP
    esr_default_text ENDS
    end
