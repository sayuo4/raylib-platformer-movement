#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "utility.hpp"
#include "physics_object.hpp"
#include "raylib-cpp.hpp"
#include <vector>


class MovingObject : public PhysicsObject
{
public:
    raylib::Vector2 velocity = raylib::Vector2::Zero();

    std::vector<PhysicsObject*> collisionList;
    bool isOnFloor = false;
    bool isOnCeiling = false;
    bool isOnWall = false;
    float wallDir = 0.0f;

    MovingObject(const float x, const float y, const float width, const float height);
    MovingObject(const raylib::Vector2& position, const raylib::Vector2& size);

    void move();
    CollisionInfo* testCollision(const raylib::Vector2& position, PhysicsObject* body);
    CollisionInfo* testMove(const raylib::Vector2& velocity);
};

#endif