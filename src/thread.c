#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "thread.h"
#include "tid.h"
#include "timer.h"
#include "switch.h"

static struct list thread_list;
static struct thread *initial_tcb;
static struct thread *current_thread;

static struct thread *get_next_thread(){
	if (list_size(&thread_list) == 0) {
		return NULL;
	}
	return list_entry(list_pop_front(&thread_list), struct thread, elem);
}

void __attribute__ ((constructor)) pthread_init() {

	/* first, initialize tid */
	if (tid_init() == -1) {
		exit(-1);
	}

	/* initialize thread list */
	list_init(&thread_list);

	/* initialize timer and signal handler */
	if (timer_init() == -1) {
		exit(-1);
	}

	/* allocate a TCB for initial thread */
	pthread_t tid = allocate_tid();
	if (tid == -1) {
		exit(-1);
	}

	initial_tcb = (void *)(0xdead000);

	if (mmap(initial_tcb, 0x1000, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0) != initial_tcb) {
		perror("mmap");
		deallocate_tid(tid);
		exit(-1);
	}

	initial_tcb->tid = tid;
	initial_tcb->magic = TCB_MAGIC;

	current_thread = initial_tcb;
}

void __attribute__ ((destructor)) pthread_fini() {

	/* initialize timer and signal handler */
	if (timer_fini() == -1) {
		exit(-1);
	}
}

void schedule(){

	struct thread *cur = current_thread;
	struct thread *next = get_next_thread();

	if (!next) {
		return;
	}
	printf("switch(%p,%p)\n",next,cur);
	context_switch(next,cur);
	current_thread = next;
	list_push_back(&thread_list, &cur->elem);
}

static void thread_start(void *(*start_routine)(void *), void *arg) {
	start_routine(arg);
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg) {
	
	struct registers regs;
	/* for now, don't allow custom attributes */
	if (attr) {
		return -1;
	}

	/* allocate a thread id */
	pthread_t tid = allocate_tid();
	if (tid == -1) {
		return -1;
	}

	/* allocate 10KB memory for new thread, stack memory may overlap*/
	void *stack_addr = (void *)(0x80000000+0x10000*tid);
	if (mmap(stack_addr, 0x10000, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE|MAP_GROWSDOWN, -1, 0) != stack_addr) {
		perror("mmap");
		deallocate_tid(tid);
		return -1;
	}

	struct thread *TCB = (struct thread *)stack_addr;

	/* need not initialize this structure due to zero on reference */
	TCB->magic = TCB_MAGIC;
	TCB->tid = tid;
	TCB->flags = 0;
	TCB->stack = (char *)stack_addr + 0x1000 - sizeof(regs);

	/* set initial registers */

	memset(&regs, 0, sizeof(regs));
	regs.rdi = start_routine;
	regs.rsi = arg;
	regs.rip = thread_start;
	memcpy((char *)TCB->stack, &regs, sizeof(regs));

	printf("offsetof(struct thread, stack) = %d\n",offsetof(struct thread, stack));


	list_push_back(&thread_list, &TCB->elem);

	return 0;
}

int pthread_join(pthread_t thread, void **retval) {
	return -1;
}

int pthread_detach(pthread_t thread) {
	/* find TCB with tid thread , if not found return -1 */
	/* set detached flag */
	return -1;
}
