#include "raycast.hpp"
#include "physics_object.hpp"


Raycast::Raycast(raylib::Vector2 position, raylib::Vector2 direction, PhysicsObject* ignoredObject) :
	position(position),
	direction(direction),
    ignoredObject(ignoredObject)
{}

bool Raycast::CheckLineCollision(raylib::Vector2 firstLineStart, raylib::Vector2 firstLineEnd,
                                 raylib::Vector2 secondLineStart, raylib::Vector2 secondLineEnd, raylib::Vector2& collisionPoint)
{
    raylib::Vector2 d1 = firstLineEnd - firstLineStart;
    raylib::Vector2 d2 = secondLineEnd - secondLineStart;

    float denom = d1.x * d2.y - d1.y * d2.x;

    if (std::abs(denom) < 1e-6f)
        return false;

    raylib::Vector2 s = secondLineStart - firstLineStart;

    float t = (s.x * d2.y - s.y * d2.x) / denom;
    float u = (s.x * d1.y - s.y * d1.x) / denom;

    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f)
    {
        collisionPoint = firstLineStart + d1 * t;
        return true;
    }

    return false;
}

bool Raycast::CheckLineRectangleCollision(raylib::Vector2 lineStart, raylib::Vector2 lineEnd,
                                          raylib::Rectangle rect, raylib::Vector2& collisionPoint)
{
    raylib::Vector2 rectVertices[4] = {
        {rect.x, rect.y},
        {rect.x + rect.width, rect.y},
        {rect.x + rect.width, rect.y + rect.height},
        {rect.x, rect.y + rect.height}
    };

    for (int i = 0; i < 4; ++i)
    {
        if (CheckLineCollision(lineStart, lineEnd, rectVertices[i], rectVertices[(i + 1) % 4], collisionPoint))
        {
            return true;
        }
    }

    return false;
}

void Raycast::fixedUpdate(float deltaTime)
{
    raylib::Vector2 collisionPoint;

    // Optimize later
    if (collisionInfo)
        delete collisionInfo;

    for (auto& physicsObject : PhysicsObject::getPhysicsObjects())
    {
        if (physicsObject == ignoredObject)
            continue;

        bool checkCollision = CheckLineRectangleCollision(position, position + direction, physicsObject->rect, collisionPoint);

        if (checkCollision)
        {
            colliding = true;
            collisionInfo = new RaycastInfo(physicsObject, collisionPoint);

            return;
        }
    }

    colliding = false;
    collisionInfo = nullptr;
}

bool Raycast::isColliding()
{
    return colliding;
}

RaycastInfo* Raycast::getCollisionInfo()
{
    return collisionInfo;
}

void Raycast::draw()
{
    raylib::Color color = isColliding() ? RED : BLUE;

    DrawLine(position.x, position.y, position.x + direction.x, position.y + direction.y, color);
}