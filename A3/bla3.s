	.file	"bla3.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$6, -12(%rbp)
	movl	$2, -4(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -8(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -12(%rbp)
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-4(%rbp), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, -8(%rbp)
.L2:
	cmpl	$0, -8(%rbp)
	jne	.L3
	cmpl	$0, -8(%rbp)
	je	.L4
	movl	$1, -12(%rbp)
.L4:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
