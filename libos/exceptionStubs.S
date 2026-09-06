.macro VECTOR_STUB section_name, stub_name, tramp_name, excsave_reg
    .section \section_name, "ax", @progbits
    .align 4
    .global \stub_name
    .type \stub_name, @function
    \stub_name:
        wsr.\excsave_reg a0
        j \tramp_name
.endm

VECTOR_STUB .WindowVectors.text,       _WindowVectorsStub,   _window_vectors_trampoline,   excsave1
VECTOR_STUB .KernelExceptionVector.text, _KernelExceptionStub, _kernel_exception_trampoline, excsave1
VECTOR_STUB .UserExceptionVector.text,   _UserExceptionStub,   _user_exception_trampoline,   excsave1
VECTOR_STUB .DoubleExceptionVector.text, _DoubleExceptionStub, _double_exception_trampoline, excsave1

VECTOR_STUB .Level2InterruptVector.text, _Level2InterruptStub, _level2_interrupt_trampoline, excsave2
VECTOR_STUB .Level3InterruptVector.text, _Level3InterruptStub, _level3_interrupt_trampoline, excsave3
VECTOR_STUB .Level4InterruptVector.text, _Level4InterruptStub, _level4_interrupt_trampoline, excsave4
VECTOR_STUB .Level5InterruptVector.text, _Level5InterruptStub, _level5_interrupt_trampoline, excsave5

VECTOR_STUB .DebugExceptionVector.text,  _DebugExceptionStub,  _debug_exception_trampoline,  excsave6
VECTOR_STUB .NMIExceptionVector.text,    _NMIExceptionStub,    _nmi_exception_trampoline,    excsave7


.macro TRAMPOLINE tramp_name, c_handler, excsave_reg, epc_reg, ret_inst
    .section .text, "ax"
    .global \tramp_name
    .align 4
    \tramp_name:
        addi a1, a1, -48
        
        s32i a2, a1, 0
        s32i a3, a1, 4
        s32i a4, a1, 8
        s32i a5, a1, 12
        s32i a6, a1, 16
        s32i a7, a1, 20
        s32i a8, a1, 24
        s32i a9, a1, 28
        s32i a10, a1, 32
        s32i a11, a1, 36
        
        rsr.\excsave_reg a2
        s32i a2, a1, 40
        
        rsr.exccause a2
        rsr.\epc_reg a3
        rsr.excvaddr a4
        
        call0 \c_handler
        
        l32i a2, a1, 40
        wsr.\excsave_reg a2
        
        l32i a11, a1, 36
        l32i a10, a1, 32
        l32i a9,  a1, 28
        l32i a8,  a1, 24
        l32i a7,  a1, 20
        l32i a6,  a1, 16
        l32i a5,  a1, 12
        l32i a4,  a1, 8
        l32i a3,  a1, 4
        l32i a2,  a1, 0
        
        addi a1, a1, 48
        rsr.\excsave_reg a0
        \ret_inst
.endm

TRAMPOLINE _window_vectors_trampoline,   windowExceptionHandler,   excsave1, epc1, rfe
TRAMPOLINE _kernel_exception_trampoline, KernelExceptionHandler, excsave1, epc1, rfe
TRAMPOLINE _user_exception_trampoline,   UserExceptionHandler,   excsave1, epc1, rfe
TRAMPOLINE _double_exception_trampoline, DoubleExceptionHandler, excsave1, epc1, rfe

TRAMPOLINE _level2_interrupt_trampoline, Level2InterruptHandler, excsave2, epc2, "rfi 2"
TRAMPOLINE _level3_interrupt_trampoline, Level3InterruptHandler, excsave3, epc3, "rfi 3"
TRAMPOLINE _level4_interrupt_trampoline, Level4InterruptHandler, excsave4, epc4, "rfi 4"
TRAMPOLINE _level5_interrupt_trampoline, Level5InterruptHandler, excsave5, epc5, "rfi 5"

TRAMPOLINE _debug_exception_trampoline,  DebugExceptionHandler,  excsave6, epc6, "rfi 6"
TRAMPOLINE _nmi_exception_trampoline,    NMIHandler,    excsave7, epc7, "rfi 7"