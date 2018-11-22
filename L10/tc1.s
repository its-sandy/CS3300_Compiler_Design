	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.globl	ret_i
	.type	ret_i, @function
ret_i:
.LF0:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movl	16(%rbp), %eax
	pushq	%rax


	popq	%rax
	jmp	.LF1

.LF1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF2:
	.size	ret_i, .-ret_i

	.globl	ret_f
	.type	ret_f, @function
ret_f:
.LF3:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	movss	16(%rbp), %xmm0
	pushq	%rax
	movss	%xmm0, (%rsp)


	popq	%rax
	jmp	.LF4

.LF4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF5:
	.size	ret_f, .-ret_f

	.globl	main
	.type	main, @function
main:
.LF6:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	subq  $4, %rsp
	subq  $4, %rsp
	subq  $4, %rsp
	movl	$5, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -8(%rbp)

	movl	-8(%rbp), %eax
	pushq	%rax


	call	ret_i
	addq  $8, %rsp
	pushq	%rax
	popq	%rax
	movl	%eax, -4(%rbp)

	movl	$0x40d00000, %eax
	pushq	%rax

	call	ret_f
	addq  $8, %rsp
	pushq	%rax
	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, -12(%rbp)

	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


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
	jmp	.LF7

.LF7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF8:
	.size	main, .-main

