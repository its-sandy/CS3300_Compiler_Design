	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.globl	pow_iii
	.type	pow_iii, @function
pow_iii:
.LF0:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movl	24(%rbp), %eax
	pushq	%rax


	movl	16(%rbp), %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	cmpl	%edx, %eax
	setg	%al
	movzbl	%al, %eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF1
	movl	$1, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF2

.LF1:

	movl	32(%rbp), %eax
	pushq	%rax


	movl	32(%rbp), %eax
	pushq	%rax


	movl	24(%rbp), %eax
	pushq	%rax


	movl	$1, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax

	movl	16(%rbp), %eax
	pushq	%rax


	call	pow_iii
	addq  $24, %rsp
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF2

.LF2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF3:
	.size	pow_iii, .-pow_iii

	.globl	pow_fii
	.type	pow_fii, @function
pow_fii:
.LF4:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movl	24(%rbp), %eax
	pushq	%rax


	movl	16(%rbp), %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	cmpl	%edx, %eax
	setg	%al
	movzbl	%al, %eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF5
	movl	$0x3f800000, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF6

.LF5:

	movss	32(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movss	32(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movl	24(%rbp), %eax
	pushq	%rax


	movl	$1, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax

	movl	16(%rbp), %eax
	pushq	%rax


	call	pow_fii
	addq  $24, %rsp
	pushq	%rax

	movss	(%rsp), %xmm1
	popq	%rbx
	movss	(%rsp), %xmm0
	popq	%rbx
	mulss	%xmm1, %xmm0
	pushq	%rbx
	movss	%xmm0, (%rsp)

	popq	%rax
	jmp	.LF6

.LF6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF7:
	.size	pow_fii, .-pow_fii

	.globl	main
	.type	main, @function
main:
.LF8:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	subq  $4, %rsp
	subq  $4, %rsp
	movl	$2, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax


	movl	$1, %eax
	pushq	%rax

	movl	$5, %eax
	pushq	%rax

	call	pow_iii
	addq  $24, %rsp
	pushq	%rax
	popq	%rax
	movl	%eax, -4(%rbp)

	movl	$0x404ccccd, %eax
	pushq	%rax

	movl	$1, %eax
	pushq	%rax

	movl	$5, %eax
	pushq	%rax

	call	pow_fii
	addq  $24, %rsp
	pushq	%rax
	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -8(%rbp)

	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	-8(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


	movl	$0, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF9

.LF9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF10:
	.size	main, .-main

