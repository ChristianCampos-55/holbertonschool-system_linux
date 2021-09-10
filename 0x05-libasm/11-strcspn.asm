BITS 64

global asm_strcspn

section .text
asm_strcspn:
        push rbp
        mov rbp, rsp
        push rcx
        push r8
        push r9
        xor rax, rax
        xor rcx, rcx
        xor r8, r8
        xor r9, r9
loop_cero:
        mov r8b, BYTE [rdi + rax]
        test r8b, r8b
        jz end
        xor rcx, rcx
loop_one:
        mov r9b, BYTE [rsi + rcx]
        test r9b, r9b
        jz ford_next
        cmp r8b, r9b
        je end
        inc rcx
        jmp loop_one
ford_next:
        inc rax
        jmp loop_cero
end:
        pop r9
        pop r8
        pop rcx
        mov rsp, rbp
        pop rbp
        ret
