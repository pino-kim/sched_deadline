/*
 * main.c
 *
 *  Created on: Jun 1, 2017
 *      Author: stefano
 */

#include <pthread.h>
#include "sched_deadline.h"

#define	NT	2

static volatile int done;
static volatile int x;

void *run_deadline(void *data)
{
struct sched_attr	attr;
int 				ret;
unsigned long int	flags = 0;

	printf("deadline thread started [%ld]\n", gettid());

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = 10 * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	ret = sched_setattr(0, &attr, flags);
	if (ret < 0) {
		done = 0;
		perror("sched_setattr");
		exit(-1);
	}

	x = 0;
	while (!done) {
		x++;
	}

	printf("deadline thread dies [%ld]\n", gettid());
	return NULL;
}

int main(int argc, char **argv)
{
pthread_t	thread;

	printf("main thread [%ld]\n", gettid());

	pthread_create(&thread, NULL, run_deadline, NULL);

	sleep(3);

	done = 1;
	pthread_join(thread, NULL);

	printf("main dies [%ld]\tx = %ld\n", gettid(), x);
	return 0;
}
