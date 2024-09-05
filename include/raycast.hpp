#ifndef RAYCAST_HPP
#define RAYCAST_HPP

#include "object.hpp"
#include "physics_object.hpp"
#include "utility.hpp"
#include "raylib-cpp.hpp"

class Raycast : public Object
{
private:
	bool colliding = false;
	RaycastInfo* collisionInfo = nullptr;
	PhysicsObject* ignoredObject;
	
	bool CheckLineCollision(raylib::Vector2 firstLineStart, raylib::Vector2 firstLineEnd,
							raylib::Vector2 secondLineStart, raylib::Vector2 secondLineEnd, raylib::Vector2& collisionPoint);
	
	bool CheckLineRectangleCollision(raylib::Vector2 lineStart, raylib::Vector2 lineEnd,
									 raylib::Rectangle rect, raylib::Vector2& collisionPoint);

	void fixedUpdate(float deltaTime) override;

public:
	raylib::Vector2 position;
	raylib::Vector2 direction;

	Raycast(raylib::Vector2 position, raylib::Vector2 direction, PhysicsObject* ignoredObject = nullptr);

	bool isColliding();
	RaycastInfo* getCollisionInfo();

	void draw();
};

#endif