#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

class Object
{
private:
	static std::vector<Object*> objects;
	// this is A COMMNET FROM  3qrooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
	//ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooob.
	static float accumulatedDeltaTime;

protected:	
	virtual void update(float deltaTime);
	virtual void fixedUpdate(float deltaTime);

public:
	Object();
	~Object();

	static void updateObjects();
	static bool isAtPhysicsFrame();
};

#endif