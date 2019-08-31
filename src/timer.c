#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include "timer.h"

timer_t timer;

void timer_start(void (*callback))
{
	// TODO change to embedded platform?

	signal(SIGALRM, callback);
	
	struct itimerspec value;

	value.it_value.tv_sec = 1;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_nsec = 0;

	timer_create(CLOCK_REALTIME, NULL, &timer);
	timer_settime(timer, 0, &value, NULL);
}

