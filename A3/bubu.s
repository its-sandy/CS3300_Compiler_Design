	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.comm	b,4,4
	.comm	c,4,4
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
	movl	$6, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-4(%rbp), %eax
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
	negl	%eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

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

