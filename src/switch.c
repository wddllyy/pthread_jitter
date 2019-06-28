#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "thread.h"
#include "switch.h"

void context_switch(struct thread *new, struct thread *old) {
	/* save registers to TCB of old thread */
	old->regs.rip = get_next_instr();
	asm volatile("mov %%rsp, %0":"=m"(old->regs.rsp));
	asm volatile("mov %%rax, %0":"=m"(old->regs.rax));
	asm volatile("mov %%rbx, %0":"=m"(old->regs.rbx));
	asm volatile("mov %%rcx, %0":"=m"(old->regs.rcx));
	asm volatile("mov %%rdx, %0":"=m"(old->regs.rdx));
	/* retreive registers from new thread */

	/* continue execution */

}