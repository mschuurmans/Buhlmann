#ifndef __TIMER_H_
#define __TIMER_H_

/*!
 * Start a timer thread.
 *
 * On unix this will be done with a timer
 * Might have to look for a cleaner solution
 * on embedded platforms for low power usage
 *
 * TODO change to embedded platform?
 */
extern void timer_start(void(*));

#endif
