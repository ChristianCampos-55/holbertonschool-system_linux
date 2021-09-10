BITS 64

global asm_strcasecmp

section .text
asm_strcasecmp:
        push rbp
	mov rbp, rsp
	push rdx
looper:
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
	jl done_tick
	cmp dl, 90
	jg done_tick
	add dx, 32

done_tick:
	cmp al, dl
	jne ford
	inc rdi
	inc rsi
	jmp looper
ford:
	cmp al, dl
	je equal
	jl less
	sub al, dl
	jmp end
equal:
	mov rax, 0x0
	jmp end
less:
	sub al, dl
	neg al
	imul eax, -1
	jmp end
end:
	pop rdx
	mov rbp, rsp
	pop rbp
	ret
