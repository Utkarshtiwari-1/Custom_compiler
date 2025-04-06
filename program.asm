%include "macros.inc"

section .data
    A dd 4
    B dd 3
    Z dd 0
    title db "Z Value", 0
    digit db 10 dup(0)

section .text
global _start

_start:
    mov eax, [A]
    imul eax, eax
    add eax, [B]
    mov [Z], eax
    mov eax, [Z]
    mov ebx, 10
    xor ecx, ecx
convert_loop:
    xor edx, edx
    div ebx
    add dl, '0'
    mov [digit + ecx], dl
    inc ecx
    test eax, eax
    jnz convert_loop
    mov byte [digit + ecx], 0
    mov esi, digit
    lea edi, [digit + ecx - 1]
reverse:
    cmp esi, edi
    jge done_reverse
    mov al, [esi]
    mov bl, [edi]
    mov [esi], bl
    mov [edi], al
    inc esi
    dec edi
    jmp reverse
done_reverse:
    push 0
    push title
    push digit
    push 0
    call [MessageBoxA]
    ret
