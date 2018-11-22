	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.globl	fun_ff
	.type	fun_ff, @function
fun_ff:
.LF0:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movss	24(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movss	16(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movss	(%rsp), %xmm1
	popq	%rbx
	movss	(%rsp), %xmm0
	popq	%rbx
	mulss	%xmm1, %xmm0
	pushq	%rbx
	movss	%xmm0, (%rsp)

	popq	%rax
	jmp	.LF1

.LF1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF2:
	.size	fun_ff, .-fun_ff

	.globl	main
	.type	main, @function
main:
.LF3:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	subq  $4, %rsp
	subq  $4, %rsp
	subq  $4, %rsp
	movl	$0x40066666, %eax
	pushq	%rax

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -4(%rbp)

	movl	$0x40000000, %eax
	pushq	%rax

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -8(%rbp)

	movss	-4(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movss	-8(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	call	fun_ff
	addq  $16, %rsp
	pushq	%rax
	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -12(%rbp)

	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	-12(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF4

.LF4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF5:
	.size	main, .-main

