#ifndef PHYSICS_OBJECT_HPP
#define PHYSICS_OBJECT_HPP

#include <vector>

#include "raylib-cpp.hpp"
#include "utility.hpp"
#include "object.hpp"

class PhysicsObject : public Object
{
private:
    static std::vector<PhysicsObject*> bodies;

public:
    raylib::Rectangle rect;

    PhysicsObject(const float x, const float y, const float width, const float height, const bool isVirtual = false);
    PhysicsObject(const raylib::Vector2& position, const raylib::Vector2& size, const bool isVirtual = false);
    ~PhysicsObject();

    CollisionInfo* checkCollision(PhysicsObject* other);
    static const std::vector<PhysicsObject*>& getBodies();
};

#endif