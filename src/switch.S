#include "switch.h"

.global get_next_instr
.func get_next_instr

get_next_instr:
	mov (%rsp),%rax
	ret
.endfunc