/**
 * This is used for both benchmarking,
 * calculating FPS and deciding when to quit
 * zooming into the figure.
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

/**
 * This uses the simple RAII principle
 * The timer starts when the timer is spawned
 * The timer stops when the timer is destroyed
 * If the header DESTRUCTOR_TIMER is defined, 
 * only then will the destructor log the amount of time 
 * the timer was alive for.
 *
 * Member Variable:
 *		m_start: Time Point of start
 */
class Timer {
public:
	Timer();
	~Timer();
	
	long long int getTimeElapsed();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

#endif // __TIMER_H__
