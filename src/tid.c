#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static unsigned long tid_bitmap;

pthread_t allocate_tid() {

	int i;
	for (i = 0; i < sizeof(tid_bitmap)*8; i++){
		if (!(tid_bitmap & (1<<i))) {
			return i;
		}
	}
	return -1;
}

int deallocate_tid(pthread_t tid) {

	if (tid >= sizeof(tid_bitmap)*8) {
		return -1;
	}

	if (tid_bitmap & (1<<tid)) {
		tid_bitmap ^= (1<<tid);
		return 0;
	}

	else {
		return -1;
	}

}

int tid_init() {
	tid_bitmap = 0;
}