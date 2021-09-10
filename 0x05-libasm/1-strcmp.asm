BITS 64

global asm_strcmp

section .text
asm_strcmp:
        push rbp
        mov rbp, rsi
        xor eax, eax
        xor rcx, rcx
strcmp_loop:
        mov dl, BYTE [rdi + rcx]
        mov dh, BYTE [rsi + rcx]
        inc rcx
        test dl, dl
        je check
        test dh, dh
        je strcmp_upper
        cmp dl, dh
        je strcmp_loop
        jmp strcmp_comp
check:
        test dh, dh
        je strcmp_end
        jmp strcmp_lower
strcmp_comp:
        cmp dl, dh
        jl strcmp_lower
        jg strcmp_upper
strcmp_upper:
        xor dl, dh
        inc eax
        jmp strcmp_end
strcmp_lower:
        xor dl, dh
        dec eax
        jmp strcmp_end
strcmp_end:
        mov rsi, rbp
        pop rbp
        ret
