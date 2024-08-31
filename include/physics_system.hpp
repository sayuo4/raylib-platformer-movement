#ifndef PHYSICS_SYSTEM_HPP
#define PHYSICS_SYSTEM_HPP

#include <Rectangle.hpp>
#include <vector>

#include "raylib-cpp.hpp"
#include "utility.hpp"


class CollisionRect : public Object
{
public:
    raylib::Rectangle rect;
    bool disabled = false;

    CollisionRect(const raylib::Vector2 position, const raylib::Vector2 size);
    CollisionRect(const float positionX, const float positionY, const float sizeX, const float sizeY);

    raylib::Vector2 getCenter() const;

    void draw() const;
};

class PhysicsSystem
{
private:
    std::vector<Object*> bodies;

public:
    friend class PhysicsBody;
    friend class StaticBody;
    friend class KinematicBody;
};

struct CollisionInfo
{
public:
    Object* collider;
    raylib::Rectangle intersection;
    raylib::Vector2 to;
};

class PhysicsBody : public Object
{
protected:
    PhysicsSystem* physicsSystem;

    PhysicsBody(CollisionRect collision, PhysicsSystem* physicsSystem = nullptr);

public:
    CollisionRect collision;

    void setPosition(const raylib::Vector2 value);
    raylib::Vector2 getPosition() const;

    CollisionInfo* checkCollision(PhysicsBody* other) const;

    friend class KinematicBody;
};

#endif