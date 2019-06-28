#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "list.h"
#include "thread.h"
#include "tid.h"
#include "timer.h"

static struct list thread_list;

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
}

void __attribute__ ((destructor)) pthread_fini() {

	/* initialize timer and signal handler */
	if (timer_fini() == -1) {
		exit(-1);
	}
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg) {
	
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

	struct thread *TCB = (struct thread *)(0x80000000+0x10000*tid+0x1000);

	/* need not initialize this structure due to zero on reference */
	TCB->magic = TCB_MAGIC;
	TCB->tid = tid;
	TCB->flags = 0;
	TCB->regs.rip = start_routine;
	TCB->regs.rsp = (void *)TCB;
	TCB->regs.rdi = arg;

	list_push_back(&thread_list,&TCB->elem);

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