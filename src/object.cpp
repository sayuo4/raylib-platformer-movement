#include "object.hpp"
#include "input_manager.hpp"
#include "utility.hpp"
#include "raylib-cpp.hpp"

#include <algorithm>

std::vector<Object*> Object::objects;
float Object::accumulatedDeltaTime = 0.0f;

Object::Object()
{
	objects.push_back(this);
}

Object::~Object()
{
	auto it = std::remove(objects.begin(), objects.end(), this);

	objects.erase(it, objects.end());
}

void Object::update(float deltaTime)
{

}

void Object::fixedUpdate(float deltaTime)
{

}

void Object::updateObjects()
{
	float deltaTime = GetFrameTime();


	InputManager::update();
	for (auto& object : objects)
		object->update(deltaTime);

	accumulatedDeltaTime += deltaTime;

	while (accumulatedDeltaTime >= FIXED_UPDATE_INTERVAL)
	{
		for (auto& object : objects)
			object->fixedUpdate(FIXED_UPDATE_INTERVAL);
		InputManager::fixedUpdate();

		accumulatedDeltaTime -= FIXED_UPDATE_INTERVAL;
	}
}