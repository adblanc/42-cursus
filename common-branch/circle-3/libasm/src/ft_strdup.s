default rel


section .text
	global _ft_strdup
	extern _malloc
	extern _ft_strlen

_ft_strdup:
	push rdi ; we save our argument
	call _ft_strlen ; we get length of it
	inc rax		; inc length to malloc length + 1
	mov rdi, rax ; we move its length in rdi
	call _malloc	; we call malloc with its length
	pop rdi		; we get back our argument
	cmp rax, 0	; we check if mallco returned null pointer
	je _finish	; if so we end and returns it
	mov rsi, rdi
	mov rdi, rax;
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
