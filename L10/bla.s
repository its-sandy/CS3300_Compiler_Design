	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.comm	x,4,4
	.comm	y,4,4
	.globl	main
	.type	main, @function
main:
.LF0:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	subq  $4, %rsp
	subq  $4, %rsp
	subq  $4, %rsp
	subq  $4, %rsp
	movl	$0x40000000, %eax
	pushq	%rax

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -4(%rbp)

	movl	$0x408570a4, %eax
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


	movss	(%rsp), %xmm1
	popq	%rbx
	movss	(%rsp), %xmm0
	popq	%rbx
	divss	%xmm1, %xmm0
	pushq	%rbx
	movss	%xmm0, (%rsp)

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -16(%rbp)

	movss	-4(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movss	-8(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movss	(%rsp), %xmm1
	popq	%rbx
	movss	(%rsp), %xmm0
	popq	%rbx
	ucomiss	%xmm0, %xmm1
	seta	%al
	movzbl	%al, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -12(%rbp)

	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	-16(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	-4(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF1

.LF1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF2:
	.size	main, .-main

