#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <functional>
#include <algorithm>

#include "raylib-cpp.hpp"


float signum(float value);

raylib::Vector2 signum(raylib::Vector2 value);

float moveToward(float current, float target, float speed);

float getInputAxis(int negativeKey, int positiveKey);


template<typename Type, typename... Params>
size_t getAddress(std::function<Type(Params...)> fn)
{
    typedef Type(fnType)(Params...);
    fnType ** fnPointer = fn.template target<fnType*>();
    return (size_t) *fnPointer;
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

class Object
{
protected:
    Object() = default;
    Signal<> deleted;

public:
    virtual ~Object() = default;
    friend class PhysicsSystem;
};

#endif