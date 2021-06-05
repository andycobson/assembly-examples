;----------------------------------------------------
; Programmer : Andrew S. Jacobson
; Date due : February 9, 2020
; Description : This program will calculate a simple math
; expression using registers and constants
; ---------------------------------------------------
.386
.model flat,stdcall

.stack 4096

ExitProcess proto,dwExitCode:dword

.data?
var1 word ?
var2 word ?
var3 word ?

.data

.code
main proc

    const1 = 1254
    const2 = -842
    const3 = 347

    mov var1,const1
    mov var2,const2
    mov var3,const3

    mov ax,var1
    add ax,var2
    add ax,var3

    invoke ExitProcess,0
main endp
end main
