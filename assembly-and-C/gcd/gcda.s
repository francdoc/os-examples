	.text
	.align	2
	.global	gcda
	.type	gcda, %function
gcda:
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]

	b	WHLCHK

LOOPBDY:
	ldr	r2, [fp, #-16] /* r2=a */
	ldr	r3, [fp, #-20] /* r3=b */
	cmp	r2, r3
	ble	ELSBR

	ldr	r3, [fp, #-16] /* r3=a */
	ldr	r2, [fp, #-20] /* r2=b */
	rsb	r3, r2, r3     /* r3=r3-r2 */
	str	r3, [fp, #-16] /* r3=a (a=a-b) */
	b	WHLCHK

ELSBR:
	ldr	r3, [fp, #-20]
	ldr	r2, [fp, #-16]
	rsb	r3, r2, r3
	str	r3, [fp, #-20]

WHLCHK:
	ldr	r2, [fp, #-16] /* r2=a */
	ldr	r3, [fp, #-20] /* r3=b */
	cmp	r2, r3         /* is a == b? */
	bne	LOOPBDY

	ldr	r3, [fp, #-16] /* r3=a */
	mov	r0, r3         /* return value is a */

        /* return a */
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr


	.text
	.align	2
	.global	gcda1
	.type	gcda1, %function
gcda1:
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
gcda1r:
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]

        cmp	r0, r1
	beq	END
	blt	LESS
	sub	r0, r0, r1
	b	gcda1r

LESS:	
	sub	r1, r1, r0 
	b	gcda1r

END:
        sub     sp, fp, #12
        ldmfd   sp, {fp, sp, lr}
        bx      lr


	.text
	.align	2
	.global	gcda2
	.type	gcda2, %function
gcda2:
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #8
gcda2r:
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]

	cmp	r0, r1
	subgt	r0, r0, r1
	sublt	r1, r1, r0
	bne	gcda2r

END2:
        sub     sp, fp, #12
        ldmfd   sp, {fp, sp, lr}
        bx      lr
