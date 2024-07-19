#pragma once

/**
 * TimeSystem
 */
class Timer
{
private:
	static double _precision;
public:
	static void InitTimer();
	//Get Second
	static double GetTick();
};



