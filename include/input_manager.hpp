#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <unordered_set>

class InputManager
{
private:
	static std::unordered_set<int> pressedKeys;
	static std::unordered_set<int> justPressedKeys;
	static std::unordered_set<int> justReleasedKeys;

	static void update();
	static void fixedUpdate();

public:
	static bool isKeyDown(int key);
	static bool isKeyPressed(int key);
	static bool isKeyReleased(int key);
	
	friend class Object;
};

#endif