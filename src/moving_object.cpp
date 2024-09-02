#include "moving_object.hpp"
#include "utility.hpp"

#include <iostream>


MovingObject::MovingObject(const float x, const float y, const float width, const float height) :
	PhysicsObject(x, y, width, height)
{}

MovingObject::MovingObject(const raylib::Vector2& position, const raylib::Vector2& size) :
    PhysicsObject(position, size)
{}

void MovingObject::move()
{
	collisionList.clear();
    isOnFloor = false;
    isOnCeiling = false;
    isOnWall = false;

    rect.SetPosition(rect.GetPosition() + velocity * FIXED_UPDATE_INTERVAL);

    for (auto& body : getBodies())
    {
        if (body == this)
            continue;

        // Optimize later
        CollisionInfo* collisionInfo = checkCollision(body);
        if (!collisionInfo)
        {
            CollisionInfo* wallCollisionInfo = testCollision(raylib::Vector2(1.0f, 0.0f), body);
            
            if (!wallCollisionInfo)
                wallCollisionInfo = testCollision(raylib::Vector2(-1.0f, 0.0f), body);

            if (wallCollisionInfo)
            {
                collisionList.push_back(body);
                
                isOnWall = true;
                wallDir = wallCollisionInfo->toSignum.x;

                delete wallCollisionInfo;
            }

            continue;
        }

        collisionList.push_back(body);

        if (collisionInfo->intersection.width < collisionInfo->intersection.height)
        {
            rect.SetPosition(rect.GetPosition() - raylib::Vector2(collisionInfo->intersection.width * collisionInfo->toSignum.x, 0.0f));
            velocity.x = 0;
            isOnWall = true;
            wallDir = collisionInfo->toSignum.x;
            std::cout << wallDir << '\n';
        }

        else
        {
            rect.SetPosition(rect.GetPosition() - raylib::Vector2(0.0f, collisionInfo->intersection.height * collisionInfo->toSignum.y));
            velocity.y = 0;

            if (collisionInfo->toSignum.y == 1)
                isOnFloor = true;
            else
                isOnCeiling = true;
        }

        delete collisionInfo;
    }
}

CollisionInfo* MovingObject::testCollision(const raylib::Vector2& velocity, PhysicsObject* body)
{
    PhysicsObject* virtualBody = new PhysicsObject(
        rect.GetPosition() + velocity,
        rect.GetSize(),
        true
    );

    CollisionInfo* collisionInfo = virtualBody->checkCollision(body);

    delete virtualBody;
    return collisionInfo;
}

CollisionInfo* MovingObject::testMove(const raylib::Vector2& velocity)
{
    PhysicsObject* virtualBody = new PhysicsObject(
        rect.GetPosition() + velocity,
        rect.GetSize(),
        true
    );

    for (auto& body : getBodies())
    {
        if (body == this)
            continue;

        CollisionInfo* collisionInfo = virtualBody->checkCollision(body);

        if (!collisionInfo)
            continue;

        delete virtualBody;
        return collisionInfo;
    }

    delete virtualBody;
    return nullptr;
}
