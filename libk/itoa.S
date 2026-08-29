.global itoa
    .type   itoa, @function
    .align  4
itoa:
    /* 
     * We are entered via call0.
     * Arguments are in a2 (value), a3 (str), a4 (radix).
     * Return address is in a0.
     * Stack pointer is in a1.
     */

    /* 
     * 1. Save call0 callee-saved registers (a12 - a15).
     * When we execute callx8, our a8-a15 become the callee's a0-a7.
     * The windowed function will likely clobber its a4-a7, meaning
     * it would permanently overwrite our a12-a15. 
     */
    addi    a1, a1, -16
    s32i    a12, a1, 0
    s32i    a13, a1, 4
    s32i    a14, a1, 8
    s32i    a15, a1, 12

    /* 
     * 2. Shift arguments to the registers expected by call8.
     * In call8, caller's a8..a15 map to the callee's a0..a7.
     * The callee expects its arguments in its a2, a3, and a4.
     */
    mov     a10, a2       /* value -> callee's a2 */
    mov     a11, a3       /* str   -> callee's a3 */
    mov     a12, a4       /* radix -> callee's a4 */

    /* 
     * 3. Pass the stack pointer.
     * The callee needs a valid SP in its a1.
     */
    mov     a9, a1        /* SP -> callee's a1 */

    /* 
     * 4. Invoke the ROM function via callx8.
     * This sets CALLINC=2, satisfying the ROM function's `entry` instruction.
     */
    movi    a8, 0x400566b4
    callx8  a8

    /* 
     * 5. Retrieve the return value.
     * The ROM function returns the string pointer in its a2, 
     * which corresponds to our a10. We move it to a2 for the call0 ABI.
     */
    mov     a2, a10

    /* 6. Restore the call0 callee-saved registers */
    l32i    a12, a1, 0
    l32i    a13, a1, 4
    l32i    a14, a1, 8
    l32i    a15, a1, 12
    addi    a1, a1, 16

    /* 7. Return to the original call0 caller */
    ret