default rel

section .text
	global _ft_strlen

_ft_strlen:
	xor rcx, rcx
_loop:
	cmp [rdi], byte 0
	je _end
	inc rcx
	inc rdi
	jmp _loop

_end:
	mov rax, rcx
	ret	
