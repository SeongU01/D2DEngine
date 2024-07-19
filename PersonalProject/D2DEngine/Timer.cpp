#include "PCH.h"
#include "Timer.h"
#include <stdexcept>

double Timer::_precision = 0.0;

void Timer::InitTimer()
{
	LARGE_INTEGER freq;
	if (!QueryPerformanceFrequency(&freq))
	{
		throw std::runtime_error("timer: performance counter is not supported.");
	}
	_precision = 1.0 / static_cast<double>(freq.QuadPart);
}

double Timer::GetTick()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return static_cast<double>(counter.QuadPart) * _precision;
}
