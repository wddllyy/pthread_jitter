/* context switch to new thread */
void context_switch(struct thread *new, struct thread *old);
/* get RIP of next instruction */
void *get_next_instr(void);