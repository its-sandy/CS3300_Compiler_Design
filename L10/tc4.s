	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.globl	func_if
	.type	func_if, @function
func_if:
.LF0:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movl	24(%rbp), %eax
	pushq	%rax


	movl	$0, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	cmpl	%edx, %eax
	setl	%al
	movzbl	%al, %eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF1
	movss	16(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movl	$0x3f000000, %eax
	pushq	%rax

	movss	(%rsp), %xmm1
	popq	%rbx
	movss	(%rsp), %xmm0
	popq	%rbx
	mulss	%xmm1, %xmm0
	pushq	%rbx
	movss	%xmm0, (%rsp)

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, 16(%rbp)

.LF1:

	movss	16(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	popq	%rax
	jmp	.LF2

.LF2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF3:
	.size	func_if, .-func_if

	.globl	func_fi
	.type	func_fi, @function
func_fi:
.LF4:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movl	16(%rbp), %eax
	pushq	%rax


	movl	$0, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	cmpl	%edx, %eax
	setl	%al
	movzbl	%al, %eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF5
	movss	24(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	movl	$0x40000000, %eax
	pushq	%rax

	movss	(%rsp), %xmm1
	popq	%rbx
	movss	(%rsp), %xmm0
	popq	%rbx
	mulss	%xmm1, %xmm0
	pushq	%rbx
	movss	%xmm0, (%rsp)

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, 24(%rbp)

.LF5:

	movss	24(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	popq	%rax
	jmp	.LF6

.LF6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF7:
	.size	func_fi, .-func_fi

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

	movl	$0x404ccccd, %eax
	pushq	%rax

	call	func_if
	addq  $16, %rsp
	pushq	%rax
	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -4(%rbp)

	movl	$0x40066666, %eax
	pushq	%rax

	movl	$3, %eax
	pushq	%rax

	call	func_fi
	addq  $16, %rsp
	pushq	%rax
	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -8(%rbp)

	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	-4(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	-8(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

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

