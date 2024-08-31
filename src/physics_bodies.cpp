#include "physics_bodies.hpp"
#include "physics_system.hpp"
#include "utility.hpp"

#include <iostream>
#include <raylib.h>


StaticBody::StaticBody(CollisionRect collision, PhysicsSystem* physicsSystem) :
	PhysicsBody(collision, physicsSystem)
{}


KinematicBody::KinematicBody(CollisionRect collision, PhysicsSystem* physicsSystem) :
	PhysicsBody(collision, physicsSystem)
{}

void KinematicBody::move()
{
	collisionList.clear();
    isOnFloor = false;
    isOnCeiling = false;
    bool currentOnWall = false;

    setPosition(getPosition() + velocity * GetFrameTime());
    if (velocity.x) lastMovingDir = signum(velocity.x);

    if (collision.disabled) return;

    for (auto& object : physicsSystem->bodies)
    {
        if (object == this) continue;

    	PhysicsBody* body = dynamic_cast<PhysicsBody*>(object);
    	if (!body) continue;

        CollisionInfo* collisionInfo = checkCollision(body);
        if (!collisionInfo) continue;

        collisionList.push_back(body);

        raylib::Vector2 toSignum = signum(collisionInfo->to);

        if (collisionInfo->intersection.width < collisionInfo->intersection.height)
        {
            setPosition(getPosition() - raylib::Vector2(collisionInfo->intersection.width * toSignum.x, 0.0));
            velocity.x = 0;
            isOnWall = true;
            currentOnWall = true;
            wallNormal = raylib::Vector2{-toSignum.x, 0.0};
        }

        else
        {
            setPosition(getPosition() - raylib::Vector2(0.0, collisionInfo->intersection.height * toSignum.y));
            velocity.y = 0;

            if (toSignum.y == 1) isOnFloor = true;
            else isOnCeiling = true;
        }

        delete collisionInfo;
    }

    if (isOnWall and !currentOnWall)
    {
        CollisionInfo* wallTestCollisionInfo = testMove(raylib::Vector2(lastMovingDir));
        if (!wallTestCollisionInfo) isOnWall = false;
        
        else
        {
            collisionList.push_back(wallTestCollisionInfo->collider);
            delete wallTestCollisionInfo;
        }
    }    
}

CollisionInfo* KinematicBody::testMove(raylib::Vector2 velocity)
{
    PhysicsBody* virtualBody = new PhysicsBody(
        CollisionRect(
            getPosition() + velocity,
            collision.rect.GetSize()
        )
    );

    for (auto& object : physicsSystem->bodies)
    {
        if (object == this) continue;

        PhysicsBody* body = dynamic_cast<PhysicsBody*>(object);
        if (!body) continue;

        CollisionInfo* collisionInfo = virtualBody->checkCollision(body);
        if (!collisionInfo) continue;

        delete virtualBody;
        return collisionInfo;
    }

    delete virtualBody;
    return nullptr;
}
