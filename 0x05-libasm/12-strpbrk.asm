BITS 64

global asm_strpbrk

section .text
asm_strpbrk:
        push rbp
        mov rbp, rsp
        xor rax, rax
        xor rcx, rcx
        xor rdx, rdx
        xor r8, r8
        xor r9, r9
        test rdi, rdi
        jz end
        test rsi, rsi
        jz end
loop_cero:
        mov r8b, BYTE [rdi + rcx]
        test r8b, r8b
        jz end
        xor rdx, rdx
loop_one:
        mov r9b, BYTE [rsi + rdx]
        test r9b, r9b
        jz ford_esp
        cmp r8b, r9b
        je setter
        inc rdx
        jmp loop_one
ford_esp:
        inc rcx
        jmp loop_cero
setter:
        mov rax, rdi
        add rax, rcx
end:
        mov rsp, rbp
        pop rbp
        ret
