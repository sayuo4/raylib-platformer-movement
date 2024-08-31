#include "physics_system.hpp"
#include "utility.hpp"
#include <Vector2.hpp>


CollisionRect::CollisionRect(const raylib::Vector2 position, const raylib::Vector2 size) :
	rect(position, size)
{}

CollisionRect::CollisionRect(const float positionX, const float positionY, const float sizeX, const float sizeY) :
	rect(positionX, positionY, sizeX, sizeY)
{}

raylib::Vector2 CollisionRect::getCenter() const
{
	return rect.GetPosition() + rect.GetSize() / 2.0f;
}

void CollisionRect::draw() const
{
#ifdef DEBUG
	rect.Draw(raylib::Color(173, 216, 130, 255 / 2));
#endif
}


PhysicsBody::PhysicsBody(CollisionRect collision, PhysicsSystem* physicsSystem) :
	collision(collision),
	physicsSystem(physicsSystem)
{
	if (physicsSystem) physicsSystem->bodies.push_back(this);
}

void PhysicsBody::setPosition(const raylib::Vector2 value)
{
	collision.rect.SetPosition(value);
}

raylib::Vector2 PhysicsBody::getPosition() const
{
	return collision.rect.GetPosition();
}

CollisionInfo* PhysicsBody::checkCollision(PhysicsBody* other) const
{
	if (!collision.rect.CheckCollision(other->collision.rect)) return nullptr;

	CollisionInfo* info = new CollisionInfo;
	info->collider = other;
	info->intersection = collision.rect.GetCollision(other->collision.rect);
	info->to = other->getPosition() - getPosition();
	info->toSignum = signum(info->to);

	return info;
}
