	.file	"bla.c"
	.comm	b,4,4
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
	movl	$6, -4(%rbp)
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -4(%rbp)
	movl	$2, b(%rip)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.comm	c,4,4
	.globl	fun
	.type	fun, @function
fun:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$6, -4(%rbp)
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -4(%rbp)
	negl	-4(%rbp)
	movl	$4, c(%rip)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	fun, .-fun
	.globl	fun1
	.type	fun1, @function
fun1:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$4, -12(%rbp)
	movl	$3, -8(%rbp)
	movl	-12(%rbp), %eax
	negl	%eax
	movl	%eax, -4(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jle	.L5
	addl	$1, -12(%rbp)
	jmp	.L4
.L5:
	cmpl	$2, -12(%rbp)
	jle	.L7
	addl	$2, -12(%rbp)
	jmp	.L4
.L7:
	addl	$3, -12(%rbp)
	nop
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	fun1, .-fun1
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
