#include "utility.hpp"

float signum(float value)
{
    return (value > 0.0) ? 1.0 : ((value < 0.0) ? -1.0 : 0.0);
}

raylib::Vector2 signum(raylib::Vector2 value)
{
	return raylib::Vector2{signum(value.x), signum(value.y)};
}

float moveToward(float current, float target, float speed)
{
	float delta = speed * GetFrameTime();

    if (current < target) return current + delta < target ? current + delta : target;
    else if (current > target) return current - delta > target ? current - delta : target;
    else return target;
}

float getInputAxis(int negativeKey, int positiveKey)
{
	bool negativePressed = raylib::Keyboard::IsKeyDown(negativeKey);
	bool positivePressed = raylib::Keyboard::IsKeyDown(positiveKey);

	if (positivePressed && !negativePressed) return 1.0;
	else if (negativePressed && !positivePressed) return -1.0;
	else return 0.0;
}
