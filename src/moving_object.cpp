#include "moving_object.hpp"
#include "utility.hpp"

MovingObject::MovingObject(const float x, const float y, const float width, const float height) :
	PhysicsObject(x, y, width, height)
{}

MovingObject::MovingObject(const raylib::Vector2& position, const raylib::Vector2& size) :
    PhysicsObject(position, size)
{}

void MovingObject::move()
{
	collisionList.clear();
    onFloor = false;
    onCeiling = false;
    onWall = false;

    rect.SetPosition(rect.GetPosition() + velocity * FIXED_UPDATE_INTERVAL);

    for (auto& physicsObject : getPhysicsObjects())
    {
        if (physicsObject == this)
            continue;

        // Optimize later
        CollisionInfo* collisionInfo = checkCollision(physicsObject);

        if (!collisionInfo)
        {
            CollisionInfo* wallCollisionInfo = testCollision(raylib::Vector2(1.0f, 0.0f), physicsObject);
            
            if (!wallCollisionInfo)
                wallCollisionInfo = testCollision(raylib::Vector2(-1.0f, 0.0f), physicsObject);

            if (wallCollisionInfo)
            {
                collisionList.push_back(physicsObject);
                
                onWall = true;
                wallDir = wallCollisionInfo->toSignum.x;

                delete wallCollisionInfo;
            }

            continue;
        }

        collisionList.push_back(physicsObject);

        if (collisionInfo->intersection.width < collisionInfo->intersection.height)
        {
            rect.SetPosition(rect.GetPosition() - raylib::Vector2(collisionInfo->intersection.width * collisionInfo->toSignum.x, 0.0f));
            velocity.x = 0;
            onWall = true;
            wallDir = collisionInfo->toSignum.x;
        }

        else
        {
            rect.SetPosition(rect.GetPosition() - raylib::Vector2(0.0f, collisionInfo->intersection.height * collisionInfo->toSignum.y));
            velocity.y = 0;

            if (collisionInfo->toSignum.y == 1)
                onFloor = true;
            else
                onCeiling = true;
        }

        delete collisionInfo;
    }
}

CollisionInfo* MovingObject::testCollision(const raylib::Vector2& velocity, PhysicsObject* physicsObject)
{
    PhysicsObject* virtualphysicsObject = new PhysicsObject(
        rect.GetPosition() + velocity * FIXED_UPDATE_INTERVAL,
        rect.GetSize(),
        true
    );

    CollisionInfo* collisionInfo = virtualphysicsObject->checkCollision(physicsObject);

    delete virtualphysicsObject;
    return collisionInfo;
}

CollisionInfo* MovingObject::testMove(const raylib::Vector2& velocity)
{
    PhysicsObject* virtualphysicsObject = new PhysicsObject(
        rect.GetPosition() + velocity * FIXED_UPDATE_INTERVAL,
        rect.GetSize(),
        true
    );

    for (auto& physicsObject : getPhysicsObjects())
    {
        if (physicsObject == this)
            continue;

        CollisionInfo* collisionInfo = virtualphysicsObject->checkCollision(physicsObject);

        if (!collisionInfo)
            continue;

        delete virtualphysicsObject;
        return collisionInfo;
    }

    delete virtualphysicsObject;
    return nullptr;
}

const std::vector<PhysicsObject*> MovingObject::getCollisionList()
{
    return collisionList;
}

bool MovingObject::isOnFloor()
{
    return onFloor;
}

bool MovingObject::isOnCeiling()
{
    return onCeiling;
}

bool MovingObject::isOnWall()
{
    return onWall;
}

float MovingObject::getWallDir()
{
    return wallDir;
}
