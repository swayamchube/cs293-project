/**
 * This is used for both benchmarking,
 * calculating FPS and deciding when to quit
 * zooming into the figure.
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

// Implementing a simple timer using the RAII principle
class Timer {
public:
	Timer();
	~Timer();
	
	long long int getTimeElapsed();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

#endif // __TIMER_H__
