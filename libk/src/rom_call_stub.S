.section .text
    .align 4
    .global rom_call_stub
    .type rom_call_stub, @function

rom_call_stub: /*supports up to 6 arg functions*/
    addi    a1, a1, -16
    s32i    a12, a1, 0
    s32i    a13, a1, 4
    s32i    a14, a1, 8
    s32i    a15, a1, 12

    mov     a10, a2
    mov     a11, a3
    mov     a12, a4
    mov     a13, a5
    mov     a14, a6
    mov     a15, a7
    mov     a9, a1

    callx8  a8

    mov     a2, a10

    l32i    a12, a1, 0
    l32i    a13, a1, 4
    l32i    a14, a1, 8
    l32i    a15, a1, 12
    addi    a1, a1, 16

    ret