	.cpu arm9tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"hwc.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Hello world in C\000"
	.text
	.align	2
	.global	hwc
	.type	hwc, %function
hwc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4
	ldr	r0, .L3
	bl	puts
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr
.L4:
	.align	2
.L3:
	.word	.LC0
	.size	hwc, .-hwc
	.ident	"GCC: (GNU) 4.3.3"
	.section	.note.GNU-stack,"",%progbits
