/*
 * RealTime.h
 *
 *  Created on: Jun 1, 2017
 *      Author: stefano
 */

#ifndef REALTIME_H_
#define REALTIME_H_

#include <time.h>

struct task_par{
	int				arg;		/**< Task argument. */
	long			wcet;		/**< Worst case execution time in ms. */
	int				period;		/**< Period (ms). */
	int				deadline;	/**< Relative deadline (ms). */
	int				priority;	/**< Task priority in [0, 99]. */
	int				dmiss;		/**< no. deadline misses. */
	struct timespec	at;			/**< Next activity time. */
	struct timespec	dl;			/**< Absolute deadline. */
};

#endif /* REALTIME_H_ */
