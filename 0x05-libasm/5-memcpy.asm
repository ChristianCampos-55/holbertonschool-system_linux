BITS 64

global asm_memcpy

section .text
asm_memcpy:
    	push rbp
    	mov rbp, rsp
        xor rax, rax
        push rdi
looper:
        test rdx, rdx
        jz end
        mov al, BYTE [rsi]
        inc rsi
        mov BYTE [rdi], al
        inc rdi
        dec rdx
        jmp looper
end:
        pop rax
        mov rsp, rbp
        pop rbp
        ret
