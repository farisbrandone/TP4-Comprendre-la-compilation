	.file	"main.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"o ---- o ---- o ---- o ---- o ---- o ---- o"
	.align 8
.LC1:
	.string	"                                         "
.LC2:
	.string	"|"
	.align 8
.LC3:
	.string	"o      Super calculateur FARIS-G200       o"
	.align 8
.LC4:
	.string	"o ---- o ---- o ---- o ---- o ---- o ---- o\n"
	.align 8
.LC5:
	.string	"Bienvenue sur le super calculateur FARIS-G200\n "
.LC6:
	.string	"Ici nous calculons tous:"
	.align 8
.LC7:
	.string	"- Op\303\251rations simple(+, -, *, /)"
	.align 8
.LC8:
	.string	"- Trigonom\303\251trie(cos, sin, tan)"
.LC9:
	.string	"- Fonction logarithmique\n"
	.align 8
.LC10:
	.string	"Exemple d'entr\303\251e d'op\303\251ration \303\240 faire:"
.LC11:
	.string	"(2*cos(30)+3)/2\n"
.LC12:
	.string	"Commencons \303\240 calculer,"
	.align 8
.LC13:
	.string	"Entrer une op\303\251ration comme indiqu\303\251 ci-dessus et appuyer sur entr\303\251e"
.LC14:
	.string	"Erreur de lecture\n"
.LC15:
	.string	"\n"
.LC16:
	.string	"R\303\251sultat: %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 272
	lea	rax, .LC0[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	mov	edi, 124
	call	putchar@PLT
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC3[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	mov	edi, 124
	call	putchar@PLT
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC4[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC5[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC6[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC7[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC8[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC9[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC10[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC11[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC12[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	edi, 1000000
	call	usleep@PLT
	lea	rax, .LC13[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	rdx, QWORD PTR stdin[rip]
	lea	rax, -272[rbp]
	mov	esi, 256
	mov	rdi, rax
	call	fgets@PLT
	test	rax, rax
	jne	.L2
	mov	rax, QWORD PTR stderr[rip]
	mov	rcx, rax
	mov	edx, 18
	mov	esi, 1
	lea	rax, .LC14[rip]
	mov	rdi, rax
	call	fwrite@PLT
	mov	eax, 1
	jmp	.L4
.L2:
	lea	rax, -272[rbp]
	lea	rdx, .LC15[rip]
	mov	rsi, rdx
	mov	rdi, rax
	call	strcspn@PLT
	mov	BYTE PTR -272[rbp+rax], 0
	lea	rax, -272[rbp]
	mov	rdi, rax
	call	evaluateExpression@PLT
	movq	rax, xmm0
	mov	QWORD PTR -8[rbp], rax
	mov	rax, QWORD PTR -8[rbp]
	movq	xmm0, rax
	lea	rax, .LC16[rip]
	mov	rdi, rax
	mov	eax, 1
	call	printf@PLT
	mov	eax, 0
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14+deb12u1) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
