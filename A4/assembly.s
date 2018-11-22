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
	subq  $36, %rsp

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

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax


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


	popq	%rdx
	popq	%rax
	addl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -12(%rbp)

	movl	$128, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -28(%rbp)

	movl	$2, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -20(%rbp)

	movl	$256, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -16(%rbp)

	movl	$8, %eax
	pushq	%rax

	movl	-12(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -24(%rbp)

	movl	-4(%rbp), %eax
	pushq	%rax

	movl	-8(%rbp), %eax
	pushq	%rax

	popq	%rdx
	popq	%rax
	imull	%edx, %eax
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
	addl	%edx, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, -28(%rbp)

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

	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	$256, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	$2, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-24(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

	movl	-28(%rbp), %eax
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

