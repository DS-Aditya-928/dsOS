.section .entry.text, "ax"
.literal_position

.global hiddenYield
.extern oldRegisters
.extern newRegisters

hiddenYield:
    entry a1, 32

    movi    a15, oldRegisters
    l32i    a15, a15, 0

    s32i    a0, a15, 0

    /*movi a15, oldRegisters*/
    movi    a15, newRegisters
    l32i    a15, a15, 0

    l32i    a0, a15, 0
    l32i    a1,  a15, 4
    l32i    a2,  a15, 8
    l32i    a3,  a15, 12
    l32i    a4,  a15, 16
    l32i    a5,  a15, 20
    l32i    a6,  a15, 24   
    l32i    a7,  a15, 28
    l32i    a8,  a15, 32
    l32i    a9,  a15, 36
    l32i    a10, a15, 40
    l32i    a11, a15, 44
    l32i    a12, a15, 48
    l32i    a13, a15, 52
    l32i    a14, a15, 56
    jx a0

    retw.n