default rel

section .text
	global _ft_strcpy

_ft_strcpy:
	mov rax, rdi ; we store dest pointer
_core:	
	cmp [rsi], byte 0
	je	_finish
	mov r8, [rsi]
	mov [rdi], r8
	inc rsi
	inc rdi
	jmp _core

_finish:
	ret
