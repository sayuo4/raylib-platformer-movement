#include "physics_object.hpp"

std::vector<PhysicsObject*> PhysicsObject::physicsObjects;

PhysicsObject::PhysicsObject(const float x, const float y, const float width, const float height, const bool isVirtual) :
	rect(x, y, width, height)
{
	if (!isVirtual)
		physicsObjects.push_back(this);
}

PhysicsObject::PhysicsObject(const raylib::Vector2& position, const raylib::Vector2& size, const bool isVirtual) :
	PhysicsObject(position.x, position.y, size.x, size.y, isVirtual)
{}

PhysicsObject::~PhysicsObject()
{
	// Later
}

CollisionInfo* PhysicsObject::checkCollision(PhysicsObject* other)
{
	if (!rect.CheckCollision(other->rect))
		return nullptr;

	return new CollisionInfo(
		other,
		rect.GetCollision(other->rect),
		other->rect.GetPosition() - rect.GetPosition()
	);
}

const std::vector<PhysicsObject*>& PhysicsObject::getPhysicsObjects()
{
	return physicsObjects;
}