#include "solid_object.hpp"

SolidObject::SolidObject(const float x, const float y, const float width, const float height) :
	PhysicsObject(x, y, width, height)
{}

SolidObject::SolidObject(const raylib::Vector2& position, const raylib::Vector2& size) :
	PhysicsObject(position, size)
{}