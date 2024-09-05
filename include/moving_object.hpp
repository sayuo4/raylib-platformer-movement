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

    MovingObject(const float x, const float y, const float width, const float height);
    MovingObject(const raylib::Vector2& position, const raylib::Vector2& size);

    void move();
    CollisionInfo* testCollision(const raylib::Vector2& position, PhysicsObject* physicsObject);
    CollisionInfo* testMove(const raylib::Vector2& velocity);

    const std::vector<PhysicsObject*> getCollisionList();

    bool isOnFloor();
    bool isOnCeiling();
    bool isOnWall();
    float getWallDir();

private:
    std::vector<PhysicsObject*> collisionList;

    bool onFloor = false;
    bool onCeiling = false;
    bool onWall = false;
    float wallDir = 0.0f;
};

#endif