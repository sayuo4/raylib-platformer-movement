#include "timer.hpp"
#include <iostream>

Timer::Timer(double waitTime, UpdateTypes updateType) :
	updateType(updateType)
{
	setWaitTime(waitTime);
}

void Timer::start()
{
	started = true;
	startTime = GetTime();
}

void Timer::stop()
{
	started = false;
	startTime = 0.0;
}

double Timer::getElapsedTime()
{
	if (isRunning())
		return GetTime() - startTime;

	return 0.0;
}

double Timer::getRemainingTime()
{
	if (isRunning())
		return waitTime - getElapsedTime();

	return 0.0;
}

bool Timer::isRunning()
{
	return started;
}

void Timer::setWaitTime(double value)
{
	if (value < 0)
	{
		waitTime = 0.0;
		std::cerr << "Can't set a timer with a time that's less than 0\n";
		
		return;
	}

	waitTime = value;
}

double Timer::getWaitTime()
{
	return waitTime;
}

void Timer::updateTime()
{
	if (!isRunning())
		return;

	if (getRemainingTime() <= 0.0)
	{
		stop();
		timeout.emit();
	}
}

void Timer::update(float deltaTime)
{
	if (!(updateType == UpdateTypes::PROCESS_UPDATE))
		return;

	updateTime();
}

void Timer::fixedUpdate(float deltaTime)
{
	if (!(updateType == UpdateTypes::PHYSICS_UPDATE))
		return;

	updateTime();
}
