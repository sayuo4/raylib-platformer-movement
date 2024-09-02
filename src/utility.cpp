#include "utility.hpp"

float signum(float value)
{
    return (value > 0.0f) ? 1.0f : ((value < 0.0f) ? -1.0f : 0.0f);
}

raylib::Vector2 signum(raylib::Vector2 value)
{
	return raylib::Vector2{signum(value.x), signum(value.y)};
}

float moveToward(float current, float target, float speed)
{
    if (current < target) return current + speed < target ? current + speed : target;
    else if (current > target) return current - speed > target ? current - speed : target;
    else return target;
}

float getInputAxis(int negativeKey, int positiveKey)
{
	bool negativePressed = raylib::Keyboard::IsKeyDown(negativeKey);
	bool positivePressed = raylib::Keyboard::IsKeyDown(positiveKey);

	if (positivePressed && !negativePressed) return 1.0f;
	else if (negativePressed && !positivePressed) return -1.0f;
	else return 0.0f;
}

CollisionInfo::CollisionInfo(PhysicsObject* collider, raylib::Rectangle intersection, raylib::Vector2 to) :
	collider(collider),
	intersection(intersection),
	to(to),
	toSignum(signum(to))
{}
