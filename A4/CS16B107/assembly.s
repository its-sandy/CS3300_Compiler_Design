	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%d"
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
	subq  $60, %rsp

	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	scanf

	leaq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	scanf

	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	scanf

	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	scanf

	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	scanf

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -32(%rbp)

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -28(%rbp)

	movl	$10, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -24(%rbp)

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -40(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	popq	%rax
	movl	%eax, -16(%rbp)

	movl	$2, %eax
	pushq	%rax

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	pushq	%rax


	movl	$40, %eax
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
	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	popq	%rax
	movl	%eax, -20(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	movl	-12(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -32(%rbp)

	jmp	.LF2
.LF1:
	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	popq	%rax
	movl	%eax, -40(%rbp)

.LF2:

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	popq	%rax
	movl	%eax, -44(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	movl	-12(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -48(%rbp)

	movl	$4, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -12(%rbp)

	movl	$2, %eax
	pushq	%rax

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -52(%rbp)

	movl	$3, %eax
	pushq	%rax

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
	pushq	%rax


	popq	%rdx
	popq	%rax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -36(%rbp)

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

	movl	$4, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-16(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	$10, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	$0, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-32(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-36(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-40(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-44(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-48(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-52(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	$0, %eax
	pushq	%rax

	popq	%rax
	jmp	.LF3

.LF3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LF4:
	.size	main, .-main

