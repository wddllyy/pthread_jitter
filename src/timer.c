#include <stdio.h>
#include <time.h>
#include <signal.h>
#include "list.h"
#include "thread.h"

static timer_t timer;

static void timer_interrupt(int signo){
	/* re-schedule */
	schedule();
}

int timer_init() {
	int success;
	struct itimerspec value;

	value.it_value.tv_sec = 1;
	value.it_value.tv_nsec = 0;

	value.it_interval.tv_sec = 0;
	value.it_interval.tv_nsec = 1;

	success = timer_create(CLOCK_REALTIME, NULL, &timer);
	if (success == -1) {
		perror("timer_create");
		return -1;
	}

	success = timer_settime(timer, 0, &value, NULL);
	if (success == -1) {
		perror("timer_settime");
		return -1;
	}

	if (signal(SIGALRM, timer_interrupt) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	return 0;
}

int timer_fini() {
	int success;
	timer_t timer;
	struct itimerspec value;

	value.it_value.tv_sec = 0;
	value.it_value.tv_nsec = 0;

	value.it_interval.tv_sec = 0;
	value.it_interval.tv_nsec = 0;

	success = timer_settime(timer, 0, &value, NULL);
	if (success == -1) {
		perror("timer_settime");
		return -1;
	}

	return 0;
}