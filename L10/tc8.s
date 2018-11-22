	.file	"filename.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"%f\n"
	.text
	.comm	rspsave,4,4
	.comm	q,4,4
	.comm	r,4,4
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

	movl	q(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	r(%rip), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

	movl	$1111, %eax
	pushq	%rax

	popq	%rax
	movl	%eax, q(%rip)

	movl	$0x448ae38e, %eax
	pushq	%rax

	movss	(%rsp), %xmm0
	popq	%rbx
	movss	%xmm0, r(%rip)

	movl	q(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf


	movq	%rsp, rspsave(%rip)
	movq	%rsp, %rbx
	andq	$15, %rbx
	subq	%rbx, %rsp
	cvtss2sd	r(%rip), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf

	movq	rspsave(%rip), %rsp

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

