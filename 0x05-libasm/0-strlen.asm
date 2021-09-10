BITS 64

global asm_strlen

section .text
asm_strlen:
        sub ecx, ecx
	    sub al, al
	    not ecx
	    cld
repne	scasb
	    not ecx
	    lea eax, [ecx-1]
	    ret
