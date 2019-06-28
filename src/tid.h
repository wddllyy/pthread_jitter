/* allocates a tid, returns tid on success and -1 on failure */
pthread_t allocate_tid();
/* deallocates a tid, returns 0 on success and -1 on failure */
int deallocate_tid(pthread_t tid);
/* initializes tid bitmap, returns 0 on success and -1 on failure */
int tid_init();