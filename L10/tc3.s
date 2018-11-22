	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.globl	add_ii
	.type	add_ii, @function
add_ii:
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
	addl	%edx, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF1

.LF1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF2:
	.size	add_ii, .-add_ii

	.globl	add_iii
	.type	add_iii, @function
add_iii:
.LF3:
	.cfi_startproc
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq  %rsp, %rbp
	.cfi_def_cfa_register 6

	subq  $4, %rsp
	movl	32(%rbp), %eax
	pushq	%rax


	movl	24(%rbp), %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax


	movl	16(%rbp), %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax


	popq	%rax
	jmp	.LF4

.LF4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF5:
	.size	add_iii, .-add_iii

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
	subq  $4, %rsp
	movl	$2, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -12(%rbp)

	movl	$3, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -16(%rbp)

	movl	-12(%rbp), %eax
	pushq	%rax


	movl	-16(%rbp), %eax
	pushq	%rax


	call	add_ii
	addq  $16, %rsp
	pushq	%rax
	popq	%rax
	movl	%eax, -4(%rbp)

	movl	-12(%rbp), %eax
	pushq	%rax


	movl	-16(%rbp), %eax
	pushq	%rax


	movl	$4, %eax
	pushq	%rax

	call	add_iii
	addq  $24, %rsp
	pushq	%rax
	popq	%rax
	movl	%eax, -8(%rbp)

	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


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

