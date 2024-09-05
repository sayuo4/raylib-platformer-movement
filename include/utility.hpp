#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "raylib-cpp.hpp"
#include <functional>
#include <algorithm>

constexpr float FIXED_UPDATE_INTERVAL = 1.0f / 60.0f;

float signum(float value);
raylib::Vector2 signum(const raylib::Vector2& value);

float moveToward(float current, float target, float speed);

float getInputAxis(int negativeKey, int positiveKey);

template<typename Type, typename... Params>
size_t getAddress(const std::function<Type(Params...)>& fn)
{
    typedef Type(fnType)(Params...);
    fnType* fnPointer = fn.template target<fnType>();
    if (fnPointer) {
        return reinterpret_cast<size_t>(fnPointer);
    } else {
        return 0;
    }
}

template <typename... Args>
class Signal
{
private:
	std::vector<std::function<void(Args...)>> handlers;

public:
	void connect(std::function<void(Args...)> function)
	{
		handlers.push_back(function);
	}

	void disconnect(std::function<void(Args...)> function)
	{
		auto it = std::remove_if(handlers.begin(), handlers.end(), [&](std::function<void(Args...)> other) {
			return getAddress(function) == getAddress(other);
		});

		handlers.erase(it, handlers.end());
	}

	void emit(Args... args)
	{
		for (const auto& function : handlers)
		{
			function(args...);
		}
	}
};

class PhysicsObject;

struct CollisionInfo
{
public:
	PhysicsObject* collider;
	raylib::Rectangle intersection;
	raylib::Vector2 to;
	raylib::Vector2 toSignum;

	CollisionInfo(PhysicsObject* collider, raylib::Rectangle intersection, raylib::Vector2 to);
};

struct RaycastInfo
{
public:
	PhysicsObject* collider;
	raylib::Vector2 intersectionPoint;

	RaycastInfo(PhysicsObject* collider, raylib::Vector2 intersectionPoint);
};

#endif