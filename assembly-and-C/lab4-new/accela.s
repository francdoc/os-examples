	.file	"accelw.c"
	.text
	.align	2
	.global	accel_f
	.type	accel_f, %function
accel_f:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #16
	str	r0, [fp, #-24]	@ float
	ldr	r3, [fp, #-24]	@ float
	str	r3, [fp, #-16]	@ float
	ldr	r3, [fp, #-16]	@ float

	mov	r0, r3  /* sets acceleration to time */

	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr
