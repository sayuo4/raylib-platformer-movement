#include "physics_bodies.hpp"
#include "physics_system.hpp"
#include "utility.hpp"


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
    isOnWall = false;

    setPosition(getPosition() + velocity * GetFrameTime());

    if (collision.disabled)
        return;

    for (auto& object : physicsSystem->bodies)
    {
        if (object == this)
            continue;

    	PhysicsBody* body = dynamic_cast<PhysicsBody*>(object);

    	if (!body)
            continue;

        // Optimize later
        CollisionInfo* collisionInfo = checkCollision(body);
        if (!collisionInfo)
        {
            CollisionInfo* wallCollisionInfo = testCollision(raylib::Vector2(1.0, 0.0), body);
            
            if (!wallCollisionInfo)
                wallCollisionInfo = testCollision(raylib::Vector2(-1.0, 0.0), body);

            if (wallCollisionInfo)
            {
                isOnWall = true;
                collisionList.push_back(body);
                delete wallCollisionInfo;
            }

            continue;
        }

        collisionList.push_back(body);

        raylib::Vector2 toSignum = signum(collisionInfo->to);

        if (collisionInfo->intersection.width < collisionInfo->intersection.height)
        {
            setPosition(getPosition() - raylib::Vector2(collisionInfo->intersection.width * toSignum.x, 0.0));
            velocity.x = 0;
            isOnWall = true;
            wallNormal = raylib::Vector2{-toSignum.x, 0.0};
        }

        else
        {
            setPosition(getPosition() - raylib::Vector2(0.0, collisionInfo->intersection.height * toSignum.y));
            velocity.y = 0;

            if (toSignum.y == 1)
                isOnFloor = true;
            else
                isOnCeiling = true;
        }

        delete collisionInfo;
    }
}

CollisionInfo* KinematicBody::testCollision(raylib::Vector2 velocity, PhysicsBody* otherBody)
{
    if (this == otherBody)
        return nullptr;

    PhysicsBody* virtualBody = new PhysicsBody(
        CollisionRect(
            getPosition() + velocity * GetFrameTime(),
            collision.rect.GetSize()
        )
    );

    CollisionInfo* collisionInfo = virtualBody->checkCollision(otherBody);

    delete virtualBody;
    return collisionInfo;
}

CollisionInfo* KinematicBody::testMove(raylib::Vector2 velocity)
{
    PhysicsBody* virtualBody = new PhysicsBody(
        CollisionRect(
            getPosition() + velocity * GetFrameTime(),
            collision.rect.GetSize()
        )
    );

    for (auto& object : physicsSystem->bodies)
    {
        if (this == object)
            continue;

        PhysicsBody* body = dynamic_cast<PhysicsBody*>(object);

        if (!body)
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
