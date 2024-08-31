#ifndef PHYSICS_BODIES_HPP
#define PHYSICS_BODIES_HPP

#include <vector>

#include "raylib-cpp.hpp"
#include "physics_system.hpp"

class StaticBody : public PhysicsBody
{
public:
    StaticBody(CollisionRect collision, PhysicsSystem* physicsSystem);
};

class KinematicBody : public PhysicsBody
{
private:
    float lastMovingDir;

public:
    raylib::Vector2 velocity = raylib::Vector2::Zero();

    std::vector<Object*> collisionList;
    bool isOnFloor = false;
    bool isOnCeiling = false;
    bool isOnWall = false;
    raylib::Vector2 wallNormal = raylib::Vector2::Zero();

    KinematicBody(CollisionRect collision, PhysicsSystem* physicsSystem);

    void move();
    CollisionInfo* testMove(raylib::Vector2 velocity);
};

#endif