#include "player.hpp"


Player::Player(CollisionRect collision, PhysicsSystem* physicsSystem) :
	KinematicBody(collision, physicsSystem)
{}

float Player::getHorizontalInput() const
{
	return ::getInputAxis(KEY_LEFT, KEY_RIGHT);
}

void Player::update()
{

}

void Player::applyGravity()
{
	velocity.y += getGravityForce() * GetFrameTime();
	 
	// velocity.y = clampf(velocity.y, -INF, getGravityLimit())
}

float Player::getGravityForce() const
{
	return (
		!IsKeyDown(KEY_Z) ? getDefaultGravityForce() * JUMP_NOT_PESSED_GRAVITY_FORCE
		: IsKeyDown(KEY_DOWN) and velocity.y >= 0.0 ? getDefaultGravityForce() * DOWN_PRESSED_GRAVITY_FORCE
		: getDefaultGravityForce()
	);
}

float Player::getDefaultGravityForce() const
{
	return velocity.y >= 0.0 ? FALLING_GRAVITY : JUMPING_GRAVITY;
}

void Player::applyMovement(float acc, float dec)
{
	float movementDir = getMovementDir();
	float speed = MAXIMUM_SPEED * getHorizontalInput();
	bool apply_acc = (
			velocity.x <= speed and movementDir == 1
			or velocity.x >= speed and movementDir == -1
	);

	float delta = apply_acc ? acc : dec;
	
	velocity.x = moveToward(velocity.x, speed, delta); 
}

float Player::getMovementDir() const
{
	return signum(velocity.x);
}

void Player::jump(float force, bool changeToJumpState)
{
	velocity.y = -force;

	if (changeToJumpState) forceStateTransition.emit("PlayerJumpingState");
}

void Player::enableJump()
{
	if (raylib::Keyboard::IsKeyPressed(KEY_Z))
	{
		jump(JUMP_FORCE);
	}
}

void Player::wallJump()
{
	float wallJumpDir = wallNormal.x;

	velocity.x = WALL_JUMP_HORIZONTAL_FORCE * wallJumpDir;
	jump(WALL_JUMP_VERTICAL_FORCE, false);

	forceStateTransition.emit("PlayerWallJumpingState");
}

void Player::enableWallJump()
{
	if (raylib::Keyboard::IsKeyPressed(KEY_Z))
	{
		wallJump();
	}
}
