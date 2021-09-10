BITS 64

global asm_strncasecmp

section .text
asm_strncasecmp:
	push rbp
	mov rbp, rsp
	mov r15, rdx
looper:
	cmp r15, 0
	jz ford
	mov rax, rdi
	mov rdx, rsi
	movzx eax, BYTE [rax]
	movzx edx, BYTE [rdx]
	cmp al, 0x0
	jne null_checker
	cmp dl, 0x0
	je ford
null_checker:
	cmp al, 65
	jl tick_a
	cmp al, 90
	jg tick_a
	add ax, 32
tick_a:
	cmp dl, 65
	jl tick_comp
	cmp dl, 90
	jg tick_comp
	add dx, 32
tick_comp:
	cmp al, dl
	jne ford
	inc rdi
	inc rsi
	dec r15
	jmp looper
ford:
	cmp al, dl
	je equal
	jl subs
	sub al, dl
	jmp end
equal:
	mov rax, 0x0
	jmp end
subs:
	sub al, dl
	neg al
	imul eax, -1
	jmp end
end:
	mov rbp, rsp
	pop rbp
	ret
