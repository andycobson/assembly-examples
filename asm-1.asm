;----------------------------------------------------
; Programmer : Andrew S. Jacobson
; Date due : February 2, 2020
; Description : This program will calculate a simple math
; expression using only registers
; ---------------------------------------------------

.386
.model flat,stdcall

.stack 4096

ExitProcess proto,dwExitCode:dword

.data

.code
main proc
    mov eax, 87d ; value A
    mov ebx, 25d ; value B
    mov ecx, 50d ; value C
    mov edx, 75d ; value D
    
    ; B = (A + B - C) - (D + A) + 145

    add edx, eax ; it's adding value A into value D
    add eax, ebx ; it's adding value B into value A
    sub eax, ecx ; it's subtracting value C from value A
    sub eax, edx ; it's subtracting value D from value A
    add eax, 145 ; it's adding 145 into value A

    mov ebx, eax ; it's copying value of A into B

    invoke ExitProcess,0
main endp
end main
