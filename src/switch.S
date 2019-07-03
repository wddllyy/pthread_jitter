.global get_next_instr
.func get_next_instr

get_next_instr:
	mov (%rsp),%rax
	ret
.endfunc

.global context_switch
.func context_switch

context_switch:

	push %r15
	push %r14
	push %r13
	push %r12
	push %r11
	push %r10
	push %r9
	push %r8
	push %rbp
	push %rsi
	push %rdi
	push %rdx
	push %rcx
	push %rbx
	push %rax

	movq %rsp, 0x18(%rsi)
	movq 0x18(%rdi), %rsp

	pop %rax
	pop %rbx
	pop %rcx
	pop %rdx
	pop %rdi
	pop %rsi
	pop %rbp
	pop %r8
	pop %r9
	pop %r10
	pop %r11
	pop %r12
	pop %r13
	pop %r14
	pop %r15
	ret

.endfunc