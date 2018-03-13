	.file	"HW1.c"
	.globl	UpperCase
	.data
	.align 32
	.type	UpperCase, @object
	.size	UpperCase, 260
UpperCase:
	.string	"Alpha"
	.zero	4
	.string	"Bravo"
	.zero	4
	.string	"China"
	.zero	4
	.string	"Delta"
	.zero	4
	.string	"Echo"
	.zero	5
	.string	"Foxtrot"
	.zero	2
	.string	"Golf"
	.zero	5
	.string	"Hotel"
	.zero	4
	.string	"India"
	.zero	4
	.string	"Juliet"
	.zero	3
	.string	"Kilo"
	.zero	5
	.string	"Lima"
	.zero	5
	.string	"Mary"
	.zero	5
	.string	"November"
	.zero	1
	.string	"Oscar"
	.zero	4
	.string	"Paper"
	.zero	4
	.string	"Quebec"
	.zero	3
	.string	"Research"
	.zero	1
	.string	"Sierra"
	.zero	3
	.string	"Tango"
	.zero	4
	.string	"Uniform"
	.zero	2
	.string	"Victor"
	.zero	3
	.string	"Whisky"
	.zero	3
	.string	"X-ray"
	.zero	4
	.string	"Yankee"
	.zero	3
	.string	"Zulu"
	.zero	5
	.globl	LowerCase
	.align 32
	.type	LowerCase, @object
	.size	LowerCase, 260
LowerCase:
	.string	"alpha"
	.zero	4
	.string	"bravo"
	.zero	4
	.string	"china"
	.zero	4
	.string	"delta"
	.zero	4
	.string	"echo"
	.zero	5
	.string	"foxtrot"
	.zero	2
	.string	"golf"
	.zero	5
	.string	"hotel"
	.zero	4
	.string	"india"
	.zero	4
	.string	"juliet"
	.zero	3
	.string	"kilo"
	.zero	5
	.string	"lima"
	.zero	5
	.string	"mary"
	.zero	5
	.string	"november"
	.zero	1
	.string	"oscar"
	.zero	4
	.string	"paper"
	.zero	4
	.string	"quebec"
	.zero	3
	.string	"research"
	.zero	1
	.string	"sierra"
	.zero	3
	.string	"tango"
	.zero	4
	.string	"uniform"
	.zero	2
	.string	"victor"
	.zero	3
	.string	"whisky"
	.zero	3
	.string	"x-ray"
	.zero	4
	.string	"yankee"
	.zero	3
	.string	"zulu"
	.zero	5
	.globl	Number
	.align 32
	.type	Number, @object
	.size	Number, 100
Number:
	.string	"zero"
	.zero	5
	.string	"First"
	.zero	4
	.string	"Second"
	.zero	3
	.string	"Third"
	.zero	4
	.string	"Fourth"
	.zero	3
	.string	"Fifth"
	.zero	4
	.string	"Sixth"
	.zero	4
	.string	"Seventh"
	.zero	2
	.string	"Eighth"
	.zero	3
	.string	"Ninth"
	.zero	4
	.section	.rodata
.LC0:
	.string	"*"
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
	jmp	.L2
.L6:
	cmpb	$47, -1(%rbp)
	jle	.L3
	cmpb	$57, -1(%rbp)
	jg	.L3
	movsbl	-1(%rbp), %eax
	subl	$48, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	$Number, %rax
	movq	%rax, %rdi
	call	puts
	jmp	.L2
.L3:
	cmpb	$64, -1(%rbp)
	jle	.L4
	cmpb	$90, -1(%rbp)
	jg	.L4
	movsbl	-1(%rbp), %eax
	subl	$65, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	$UpperCase, %rax
	movq	%rax, %rdi
	call	puts
	jmp	.L2
.L4:
	cmpb	$96, -1(%rbp)
	jle	.L5
	cmpb	$122, -1(%rbp)
	jg	.L5
	movsbl	-1(%rbp), %eax
	subl	$97, %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	$LowerCase, %rax
	movq	%rax, %rdi
	call	puts
	jmp	.L2
.L5:
	movl	$.LC0, %edi
	call	puts
.L2:
	call	getchar
	movb	%al, -1(%rbp)
	cmpb	$63, -1(%rbp)
	jne	.L6
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
