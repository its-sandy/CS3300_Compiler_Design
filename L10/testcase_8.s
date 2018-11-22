	.file	"testcase_8.c"
	.comm	q,4,4
	.comm	r,4,4
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
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
	movl	q(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movss	r(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movl	$1111, q(%rip)
	movss	.LC2(%rip), %xmm0
	movss	%xmm0, r(%rip)
	movl	q(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movss	r(%rip), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC2:
	.long	1149952910
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
