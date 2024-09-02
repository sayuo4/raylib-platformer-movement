#include "input_manager.hpp"
#include "raylib-cpp.hpp"
#include <unordered_set>
#include <algorithm>
#include <iostream>

std::unordered_set<int> InputManager::pressedKeys;
std::unordered_set<int> InputManager::justPressedKeys;
std::unordered_set<int> InputManager::justReleasedKeys;

void InputManager::update()
{
    for (int key : pressedKeys)
    {
        if (!raylib::Keyboard::IsKeyDown(key))
        {
        	pressedKeys.erase(key);
            justReleasedKeys.insert(key);
        }
    }

    int pressedKey = GetKeyPressed();

    if (pressedKey != 0)
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
    return pressedKeys.find(key) != pressedKeys.end();
}

bool InputManager::isKeyPressed(int key)
{
    return justPressedKeys.find(key) != justPressedKeys.end();
}

bool InputManager::isKeyReleased(int key)
{
    return justReleasedKeys.find(key) != justReleasedKeys.end();
}
