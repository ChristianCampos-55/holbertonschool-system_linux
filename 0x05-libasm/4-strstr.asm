BITS 64

global asm_strstr

section .text
asm_strstr:
    	push rbp
    	mov rbp, rsp
        push rcx
        push r8
        push r9
        xor rax, rax
        xor rcx, rcx
        xor r8, r8
        xor r9, r9
        cmp [rsi], byte 0
        je comp
        cmp [rdi], byte 0
        je end
looper:
        movzx r8, BYTE [rdi + rcx]
        movzx r9, BYTE [rsi + rcx]
        cmp r8b, byte 0
        je comp
        cmp r9b, byte 0
        je comp
        cmp r8, r9
        je ford
        inc rdi
        xor rcx, rcx
        jmp looper
ford:
        inc rcx
        jmp looper
comp:
        test r9b, r9b
        jnz end
        mov rax, rdi
end:
        pop r9
        pop r8
        pop rcx
        mov rsp, rbp
        pop rbp
        ret
