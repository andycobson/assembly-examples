.386
.model flat,stdcall

.stack 4096

ExitProcess proto,dwExitCode:dword

.data
array1 WORD 20,30,40,50,60,70,80,90,100,200
tad WORD 30
total WORD ?
count BYTE ?


.code
main proc
    mov count, LENGTHOF array1
    MOV ax, [array1]
    ADD ax, [array1+2]
    ADD ax, [array1 + 4]
    ADD ax, [array1 + 6]
    ADD ax, [array1 + 8]
    ADD ax, [array1 + 10]
    ADD ax, [array1 + 12]
    ADD ax, [array1 + 14]
    ADD ax, [array1 + 16]
    ADD ax, [array1 + 18]
    MOV total, ax

    MOV bl, count

    invoke ExitProcess,0
main endp
end main
