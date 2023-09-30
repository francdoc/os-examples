.data

msg:

        .ascii  "Hellow, ARM Assembly!\n"
len = . - msg

.text

.globl hwa
.type  hwa, %function
hwa:

        /* Save stack pointer into ip, store registers onto stack */
        mov     ip, sp
        stmfd   sp!, {fp, ip, lr, pc} /* ARM store multiple instruction */
        sub     fp, ip, #4


        /* syscall write(int fd, const void *buf, size_t count) */
        mov     %r0, $1         /* fd -> stdiou */
        ldr     %r1, =msg       /* buf -> msg */
        ldr     %r2, =len       /* count -> len(msg) */
        mov     %r7, $4         /* write is syscall #4 */
        swi     $0              /* invoke syscall */

        /* restore registers from stack */ 
        sub     sp, fp, #12
        ldmfd   sp, {fp, sp, lr}

        /* return from fuction using link register */ 
        bx      lr

