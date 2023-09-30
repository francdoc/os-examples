.myvars:
        .word   g
        .word   5679
        .word   h
        .word   4369
        .word   f
        .comm   g,4,4
        .comm   h,4,4
        .comm   f,4,4

.text
.global _start

_start:
        ldr     r2, .myvars     /* load address of g into r2 */
        ldr     r3, .myvars+4   /* load 5679=0xDDDD into r3 */
        str     r3, [r2, #0]    /* store 0xDDDD into g pointed to by r2 */
        ldr     r2, .myvars+8   /* load address of f into r2 */
        ldr     r3, .myvars+12  /* load 4369=0x1111 into r3 */
        str     r3, [r2, #0]    /* store 0x1111 into f pointed to by r2 */
        ldr     r3, .myvars     /* load address of g into r3 */
        ldr     r2, [r3, #0]    /* load contents of g into r2 */
        ldr     r3, .myvars+8   /* load address of h into r3 */
        add     r2, r2, r3      /* r2 = g + h */
        ldr     r3, .myvars+16  /* load address of f into r3 */
        str     r2, [r3, #0]    /* store (g + h) in r2 into f */

        mov     r0, $0          /* exit() call */
        mov     r7, $1
        swi     $3
