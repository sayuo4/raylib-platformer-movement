#ifndef SOLID_OBJECT_HPP
#define SOLID_OBJECT_HPP

#include "physics_object.hpp"
#include "raylib-cpp.hpp"

class SolidObject : public PhysicsObject
{
public:
    SolidObject(const float x, const float y, const float width, const float height);
    SolidObject(const raylib::Vector2& position, const raylib::Vector2& size);
};

#endif