	.text
	.align	2
	.global	sw2a
	.type	sw2a, %function
sw2a:
        mov     ip, sp
        stmfd   sp!, {fp, ip, lr, pc}
        sub     fp, ip, #4
        sub     sp, sp, #16
        str     r0, [fp, #-24]
        str     r1, [fp, #-28]

        ldr     r3, [fp, #-24] /* r3=x */
        str     r3, [fp, #-16] /* temp=r3 (temp=x) */
        ldr     r3, [fp, #-28] /* r3=y */
        str     r3, [fp, #-24] /* x=r3 (x=y) */
        ldr     r3, [fp, #-16] /* r3=temp */
        str     r3, [fp, #-28] /* y=r3 (y=x) */

        /* return */
        sub     sp, fp, #12
        ldmfd   sp, {fp, sp, lr}
        bx      lr


	.text
	.align	2
	.global	swapa
	.type	swapa, %function
swapa:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]


        /* temp = v[k] */
	ldr	r3, [fp, #-28]
	mov	r2, r3, asl #2
	ldr	r3, [fp, #-24]
	add	r3, r3, r2
	ldr	r3, [r3, #0]
	str	r3, [fp, #-16]

        /* v[k] = v[k+1] */
	ldr	r3, [fp, #-28]
	mov	r2, r3, asl #2
	ldr	r3, [fp, #-24]
	add	r1, r3, r2
	ldr	r3, [fp, #-28]
	add	r3, r3, #1
	mov	r2, r3, asl #2
	ldr	r3, [fp, #-24]
	add	r3, r3, r2
	ldr	r3, [r3, #0]
	str	r3, [r1, #0]

        /* v[k+1] = temp */
	ldr	r3, [fp, #-28]
	add	r3, r3, #1
	mov	r2, r3, asl #2
	ldr	r3, [fp, #-24]
	add	r2, r3, r2
	ldr	r3, [fp, #-16]
	str	r3, [r2, #0]


        /* return */
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr

	.align	2
	.global	sorta
	.type	sorta, %function
sorta:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]


        /* i=0 */
	mov	r3, #0
	str	r3, [fp, #-20]
	b	OLPTST

OLPBDY:
        /* j=i-1 */
	ldr	r3, [fp, #-20]
	sub	r3, r3, #1
	str	r3, [fp, #-16]
	b	ILPTST

ILPBDY:
        /* swap(v,j) */
	ldr	r0, [fp, #-24]
	ldr	r1, [fp, #-16]
	bl	swapa

        /* j -= 1 */
	ldr	r3, [fp, #-16]
	sub	r3, r3, #1
	str	r3, [fp, #-16]

ILPTST:
        /* j >= 0 is false, skip next part of test */
	ldr	r3, [fp, #-16]
	cmp	r3, #0
	blt	OLPND

	ldr	r3, [fp, #-16]  /* r3=j */
	mov	r2, r3, asl #2  /* shift left 2 */
	ldr	r3, [fp, #-24]  /* r3=v */
	add	r3, r3, r2      /* v[j+1] */

	ldr	r1, [r3, #0]    /* r1=v[j+1] */
	ldr	r3, [fp, #-16]  /* r3=j */
	add	r3, r3, #1

	mov	r2, r3, asl #2
	ldr	r3, [fp, #-24]
	add	r3, r3, r2
	ldr	r3, [r3, #0]
	cmp	r1, r3
	bgt	ILPBDY

OLPND:
	ldr	r3, [fp, #-20]
	add	r3, r3, #1
	str	r3, [fp, #-20]


        /* i < n */
OLPTST:
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-28]
	cmp	r2, r3
	blt	OLPBDY


        /* return */
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr
