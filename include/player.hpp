#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "moving_object.hpp"
#include "utility.hpp"
#include "timer.hpp"
#include <string>

class Player : public MovingObject
{
private:
	Signal<std::string> forceStateTransition;

public:
	// Movement
	const float MAXIMUM_SPEED = 450.0f;

	// On Floor
	const float RUNNING_ACC = 40.0f;
	const float RUNNING_DEC = 44.0f;

	// In Air
	const float JUMPING_ACC = 34.0f;
	const float JUMPING_DEC = 32.0f;
	const float FALLING_ACC = 32.0f;
	const float FALLING_DEC = 30.0f;
	const float WALL_JUMPING_ACC = 34.0f;
	const float WALL_JUMPING_DEC = 32.0f;
	const float WALL_JUMPING_TOWARDS_WALL_DEC = 28.0f;
	const float WALL_SLIDING_ACC = 50.0f;

	// Gravity
	const float JUMP_NOT_PESSED_GRAVITY_FORCE = 1.6f;
	const float DOWN_PRESSED_GRAVITY_FORCE = 2.4f;
	const float GRAVITY_LIMIT = 1000.0f;
	const float DOWN_PRESSED_GRAVITY_LIMIT = 1.5f;

	// Jump
	const float JUMP_HEIGHT = 112.0f;
	const float JUMP_TIME_TO_PEAK = 0.4f;
	const float JUMP_TIME_TO_LAND = 0.3f;
	const float JUMP_FORCE = (2.0f * JUMP_HEIGHT) / JUMP_TIME_TO_PEAK;
	const float JUMPING_GRAVITY = (2.0f * JUMP_HEIGHT) / (JUMP_TIME_TO_PEAK * JUMP_TIME_TO_PEAK);
	const float FALLING_GRAVITY = (2.0f * JUMP_HEIGHT) / (JUMP_TIME_TO_LAND * JUMP_TIME_TO_LAND);

	// Wall jump
	const float WALL_JUMP_HORIZONTAL_FORCE = 600.0f;
	const float WALL_JUMP_VERTICAL_FORCE = 550.0f;
	const float WALL_JUMP_DISTANCE = 8.0f;

	// Wall slide
	const float WALL_SLIDING_SPEED = 200.0f;
	const float DOWN_PRESSED_WALL_SLIDING_SPEED = 2.0f;

	// Timers
	Timer bufferJumpTimer = Timer(0.1);
	Timer coyoteJumpTimer = Timer(0.1);

	Player(const float x, const float y, const float width, const float height);
	Player(const raylib::Vector2& position, const raylib::Vector2& size);

	float getHorizontalInput() const;
	
	void applyGravity(float deltaTime);
	
	float getGravityForce() const;
	
	float getDefaultGravityForce() const;
	
	void applyMovement(float acc, float dec);
	
	float getMovementDir() const;
	
	void jump(float force, bool changeToJumpState = true);
	
	void enableJump();
	
	void wallJump();
	
	void enableWallJump();

	bool canWallSlide();

	float getWallSlidingSpeed();

	void enableWallSlide();

	void enableBufferJumpTimer();

	friend class PlayerStateMachine;
};

#endif