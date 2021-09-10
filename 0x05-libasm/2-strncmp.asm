BITS 64

global asm_strncmp

section .text
asm_strncmp:
        push rbp
        mov rbp, rsp
        xor rcx, rcx
looper:
        cmp rcx, rdx
        je comp
        mov al, [rdi + rcx]
        mov bl, [rsi + rcx]
        test al, al
        jz comp
        test bl, bl
        jz comp
        cmp al, bl
        jne comp
        inc rcx
        jmp looper
comp:
        cmp al, bl
        jl strncmp_lower
        jg strncmp_upper
        je equals
strncmp_upper:
        mov rax, 1
        jmp end
strncmp_lower:
        mov rax, -1
        jmp end
equals:
        mov rax, 0
end:
        pop rcx
        mov rsp, rbp
        pop rbp
        ret
