	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
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
	movl	$10, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	$10, %eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF1
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

.LF1:

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	$0, %eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF2
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

.LF2:

	movl	$10, %eax
	pushq	%rax

	popq	%rax
	negl	%eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	$10, %eax
	pushq	%rax

	popq	%rax
	negl	%eax
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	je	.LF3
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

.LF3:

.LF4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF5:
	.size	main, .-main

