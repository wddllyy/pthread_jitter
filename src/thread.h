#define TCB_MAGIC 0x424354
#define THREAD_DETACHED 1<<1
#define THREAD_EXITED 1<<2

struct registers {
	void *rax;
	void *rbx;
	void *rcx;
	void *rdx;
	void *rdi;
	void *rsi;
	void *rbp;
	void *rsp;
	void *r8;
	void *r9;
	void *r10;
	void *r11;
	void *r12;
	void *r13;
	void *r14;
	void *r15;
	void *rip;
};

struct thread {
	int magic;
	pthread_t tid;
	int flags;
	struct registers regs;
	struct list_elem elem;
};

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
int pthread_join(pthread_t thread, void **retval);
int pthread_detach(pthread_t thread); 
