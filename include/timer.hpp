#ifndef TIMER_HPP
#define TIMER_HPP

#include "object.hpp"
#include "utility.hpp"

class Timer : public Object
{
public:
	enum class UpdateTypes {
		PROCESS_UPDATE,
		PHYSICS_UPDATE
	};

	UpdateTypes updateType;
	
	Signal<> timeout;

	Timer(double waitTime = 0.0, UpdateTypes updateType = UpdateTypes::PROCESS_UPDATE);

	void setWaitTime(double value);
	double getWaitTime();

	void start();
	void stop();

	double getElapsedTime();
	double getRemainingTime();
	bool isRunning();

private:
	bool started = false;

	double waitTime;
	double startTime = 0.0;

	void updateTime();

	void update(float deltaTime) override;
	void fixedUpdate(float deltaTIme) override;
};

#endif