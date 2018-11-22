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
	subq  $4, %rsp
	subq  $4, %rsp
	movl	$5, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

	movl	$3000, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -8(%rbp)

	movl	$4000, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -12(%rbp)

	jmp	.LF1
.LF2:
	subq  $4, %rsp
	movl	-8(%rbp), %eax
	pushq	%rax

	movl	-4(%rbp), %eax
	pushq	%rax

	popq	%rbx
	popq	%rax
	cltd
	idivl	%ebx
	pushq	%rax


	movl	-12(%rbp), %eax
	pushq	%rax

	movl	-4(%rbp), %eax
	pushq	%rax

	popq	%rbx
	popq	%rax
	cltd
	idivl	%ebx
	pushq	%rax


	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -16(%rbp)

	movl	-16(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	$1, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	subl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -4(%rbp)

.LF1:
	movl	-4(%rbp), %eax
	pushq	%rax

	movl	$0, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	cmpl	%edx, %eax
	setg	%al
	movzbl	%al, %eax
	pushq	%rax


	movl	$5, %eax
	pushq	%rax

	movl	-4(%rbp), %eax
	pushq	%rax

	popq	%rbx
	popq	%rax
	cltd
	idivl	%ebx
	pushq	%rax


	movl	$0, %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	cmpl	%edx, %eax
	setge	%al
	movzbl	%al, %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	cmpl	$0, %eax
	je	.LF3
	cmpl	$0, %edx
	je	.LF3
	movl	$1, %eax
	jmp	.LF4
.LF3:
	movl	$0, %eax
.LF4:
	pushq	%rax

	popq %rax
	cmpl	$0, %eax
	jne	.LF2

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF5

.LF5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF6:
	.size	main, .-main

