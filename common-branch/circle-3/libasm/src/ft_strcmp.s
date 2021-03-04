default rel

section .text
	global _ft_strcmp

_ft_strcmp:
	and r8, 0
	and r9, 0
_core:
	mov r8b, byte[rdi]	; s1 byte
	mov r9b, byte[rsi]	; s2 byte
	cmp r8b, r9b	; we compare s1 and s2 bytes
	jne _end ; if they are !=, goto _end
	cmp r8b, byte 0
	je _end
	cmp r9b, byte 0
	je _end
	inc rdi
	inc rsi
	jmp _core
_end:
	sub r8, r9
	mov rax, r8	; we return != between s1 and s2 bytes
	ret

