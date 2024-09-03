#include "input_manager.hpp"
#include "object.hpp"
#include "raylib-cpp.hpp"
#include <unordered_set>

std::unordered_set<int> InputManager::pressedKeys;
std::unordered_set<int> InputManager::justPressedKeys;
std::unordered_set<int> InputManager::justReleasedKeys;

void InputManager::update()
{
    std::unordered_set<int> keysToRemove;

    for (int key : pressedKeys)
    {
        if (!InputManager::isKeyDown(key))
        {
            keysToRemove.insert(key);
            justReleasedKeys.insert(key);
        }
    }

    for (int key : keysToRemove)
    {
        pressedKeys.erase(key);
    }

    int pressedKey = GetKeyPressed();

    if (pressedKey)
    {
        pressedKeys.insert(pressedKey);
        justPressedKeys.insert(pressedKey);
    }
}

void InputManager::fixedUpdate()
{
    justPressedKeys.clear();
    justReleasedKeys.clear();
}

bool InputManager::isKeyDown(int key)
{
    return IsKeyDown(key);
}

bool InputManager::isKeyPressed(int key)
{
    if (Object::isAtPhysicsFrame())
        return justPressedKeys.find(key) != justPressedKeys.end();

    return IsKeyPressed(key);
}

bool InputManager::isKeyReleased(int key)
{
    if (Object::isAtPhysicsFrame())
        return justReleasedKeys.find(key) != justReleasedKeys.end();

    return IsKeyReleased(key);
}
