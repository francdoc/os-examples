	.global	__aeabi_fmul
	.text
	.align	2
	.global	integrator
	.type	integrator, %function
integrator:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]	@ float
	str	r1, [fp, #-20]	@ float
	str	r2, [fp, #-24]
	ldr	r3, [fp, #-24]
	ldr	r0, [fp, #-16]	@ float

	mov	lr, pc
	bx	r3
	mov	r3, r0
	mov	r0, r3
	ldr	r1, [fp, #-20]	@ float
	bl	__aeabi_fmul
	mov	r3, r0
	mov	r0, r3

	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr
