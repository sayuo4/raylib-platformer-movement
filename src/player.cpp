#include "player.hpp"
#include "input_manager.hpp"


Player::Player(float x, float y, float width, float height) :
	MovingObject(x, y, width, height)
{}

Player::Player(const raylib::Vector2& position, const raylib::Vector2& size) :
	MovingObject(position, size)
{}

float Player::getHorizontalInput() const
{
	return ::getInputAxis(KEY_LEFT, KEY_RIGHT);
}

void Player::applyGravity(float deltaTime)
{
	velocity.y += getGravityForce() * deltaTime;
	 
	// velocity.y = clampf(velocity.y, -INF, getGravityLimit())
}

float Player::getGravityForce() const
{
	return (
		!InputManager::isKeyDown(KEY_Z) ? getDefaultGravityForce() * JUMP_NOT_PESSED_GRAVITY_FORCE
		: InputManager::isKeyDown(KEY_DOWN) and velocity.y >= 0.0f ? getDefaultGravityForce() * DOWN_PRESSED_GRAVITY_FORCE
		: getDefaultGravityForce()
	);
}

float Player::getDefaultGravityForce() const
{
	return velocity.y >= 0.0f ? FALLING_GRAVITY : JUMPING_GRAVITY;
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

	if (changeToJumpState)
		forceStateTransition.emit("PlayerJumpingState");
}

void Player::enableJump()
{
	if (InputManager::isKeyPressed(KEY_Z))
	{
		jump(JUMP_FORCE);
	}
}

void Player::wallJump()
{
	float wallJumpDir = -getWallDir();

	velocity.x = WALL_JUMP_HORIZONTAL_FORCE * wallJumpDir;
	jump(WALL_JUMP_VERTICAL_FORCE, false);

	forceStateTransition.emit("PlayerWallJumpingState");
}

void Player::enableWallJump()
{
	if (InputManager::isKeyPressed(KEY_Z) && isOnWall())
	{
		wallJump();
	}
}

bool Player::canWallSlide()
{
	float inputDir = signum(getHorizontalInput());

	bool isMovingToTheWall = (inputDir == getWallDir()) && isOnWall();

	return isMovingToTheWall && inputDir != 0.0f;
}

float Player::getWallSlidingSpeed()
{
	return InputManager::isKeyDown(KEY_DOWN) ?
			(WALL_SLIDING_SPEED * DOWN_PRESSED_WALL_SLIDING_SPEED) : WALL_SLIDING_SPEED;
}

void Player::enableWallSlide()
{
	if (canWallSlide())
		forceStateTransition.emit("PlayerWallSlidingState");
}
