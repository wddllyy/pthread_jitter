#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void loop(void *arg) {
	unsigned long _arg = (unsigned long)arg;
	while(1) {
		//printf("looping at thread %ld\n",_arg);
	};
}



int main(int argc, char **argv){
	pthread_t looper;
	int i;

	for (i = 1; i < 10; i++) {
		pthread_create(&looper,NULL,loop,i);
	}
	

	while(1){
		//printf("looping at main thread\n");
	}
	
	return 0;
}
