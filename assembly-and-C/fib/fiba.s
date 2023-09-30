.text
.align	2
.global	fiba
.type	fiba, %function
fiba:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #24

	str	r0, [fp, #-32]  /* save arg n in frame */

        /* Local variable declaration and initialization */
	mov	r3, #0          /* load 0 into r3 */
	str	r3, [fp, #-28]  /* save f=0 */

	mov	r3, #0          /* load 0 into r3 */
	str	r3, [fp, #-24]  /* save f0=0 */

	mov	r3, #1          /* load 1 into r3 */
	str	r3, [fp, #-20]  /* save f1=1 */

	mov	r3, #1          /* load 1 into r3 */
	str	r3, [fp, #-16]  /* save i=1 */

DOLOOP:
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]  /* i++; */

	ldr	r2, [fp, #-24]  /* f0 */
	ldr	r3, [fp, #-20]  /* f1 */
	add	r3, r2, r3
	str	r3, [fp, #-28]  /* f=f0+f1 */

	ldr	r3, [fp, #-20]
	str	r3, [fp, #-24]  /* f0=f1; */

	ldr	r3, [fp, #-28]
	str	r3, [fp, #-20]  /* f1=f */

	ldr	r2, [fp, #-16]  /* i */
	ldr	r3, [fp, #-32]  /* n */

        /* while i < n */
	cmp	r2, r3
	bcc	DOLOOP

        /* return f in result register r0 */
	ldr	r3, [fp, #-28]
	mov	r0, r3

        /* return from function */
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr
