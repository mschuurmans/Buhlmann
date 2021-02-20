#ifndef __TIMER_H_
#define __TIMER_H_

/*
 * Start a timer thread.
 *
 * On unix this will be done with a timer
 * Might have to look at a cleaner solution
 * on embedded platforms for low power usage
 *
 * TODO change to something for an embedded platform.
 */
extern void timer_start(void(*));

#endif
