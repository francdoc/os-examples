	.syntax unified
	.arch armv7-a
	.eabi_attribute 27, 3
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.thumb
	.file	"subsp385.c"
	.text
	.align	2
	.thumb
	.thumb_func
	.type	localfunct_E_in_A.1891, %function
localfunct_E_in_A.1891:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	localfunct_E_in_A.1891, .-localfunct_E_in_A.1891
	.align	2
	.global	globalfunct_A
	.thumb
	.thumb_func
	.type	globalfunct_A, %function
globalfunct_A:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	globalfunct_A, .-globalfunct_A
	.align	2
	.thumb
	.thumb_func
	.type	localfunct_C_in_B.1897, %function
localfunct_C_in_B.1897:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	localfunct_C_in_B.1897, .-localfunct_C_in_B.1897
	.align	2
	.thumb
	.thumb_func
	.type	localfunct_B_in_A.1894, %function
localfunct_B_in_A.1894:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	localfunct_B_in_A.1894, .-localfunct_B_in_A.1894
	.align	2
	.thumb
	.thumb_func
	.type	localfunct_D_in_B.1900, %function
localfunct_D_in_B.1900:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	localfunct_D_in_B.1900, .-localfunct_D_in_B.1900
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2"
	.section	.note.GNU-stack,"",%progbits
