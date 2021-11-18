#include "Timer.h"

Timer::Timer() {
	m_start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
	// TODO: Implement a destructor here.
}

long long int Timer::getTimeElapsed() {
	auto m_now = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start).time_since_epoch().count();

	auto now = std::chrono::time_point_cast<std::chrono::microseconds>(m_now).time_since_epoch().count();

	auto duration = now - start;

	return duration;
}
