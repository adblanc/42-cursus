default rel

section .text
	global _ft_read

_ft_read:
	mov rax, 0x2000003 ; syscall read
	syscall;
	cmp rdx, 0
	je	_success ; rdx == 0 if success
	mov rax, -1
	ret
	
_success:
	ret

	
