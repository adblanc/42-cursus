default rel

section .text
	global _ft_write
_ft_write:
	mov rax, 0x2000004 ; write syscall
	syscall
	cmp rdx, 0 ; if rdx == 0 success else error
	je	_success
	mov rax, -1
	ret

_success:
	ret
