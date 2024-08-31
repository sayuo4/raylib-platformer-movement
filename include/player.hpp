#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "utility.hpp"
#include "physics_system.hpp"
#include "physics_bodies.hpp"


class Player : public KinematicBody
{
private:
	Signal<std::string> forceStateTransition;

public:
	// Movement
	const float MAXIMUM_SPEED = 450.0;

	// On Floor
	const float RUNNING_ACC = 3800.0;
	const float RUNNING_DEC = 4200.0;

	// In Air
	const float JUMPING_ACC = 3200.0;
	const float JUMPING_DEC = 3000.0;
	const float FALLING_ACC = 3000.0;
	const float FALLING_DEC = 2800.0;
	const float WALL_JUMPING_ACC = 3200.0;
	const float WALL_JUMPING_DEC = 2000.0;
	const float WALL_JUMPING_TOWARDS_WALL_DEC = 1800.0;

	// Gravity
	const float JUMP_NOT_PESSED_GRAVITY_FORCE = 1.6;
	const float DOWN_PRESSED_GRAVITY_FORCE = 2.4;
	const float GRAVITY_LIMIT = 1000.0;
	const float DOWN_PRESSED_GRAVITY_LIMIT = 1.5;

	// Jump
	const float JUMP_HEIGHT = 112.0;
	const float JUMP_TIME_TO_PEAK = 0.4;
	const float JUMP_TIME_TO_LAND = 0.3;
	const float JUMP_FORCE = (2.0 * JUMP_HEIGHT) / JUMP_TIME_TO_PEAK;
	const float JUMPING_GRAVITY = (2.0 * JUMP_HEIGHT) / (JUMP_TIME_TO_PEAK * JUMP_TIME_TO_PEAK);
	const float FALLING_GRAVITY = (2.0 * JUMP_HEIGHT) / (JUMP_TIME_TO_LAND * JUMP_TIME_TO_LAND);

	// Wall jump
	const float WALL_JUMP_HORIZONTAL_FORCE = 600.0;
	const float WALL_JUMP_VERTICAL_FORCE = 550.0;

	Player(CollisionRect collision, PhysicsSystem* physicsSystem);

	float getHorizontalInput() const;

	void update();

	void applyGravity();
	
	float getGravityForce() const;
	
	float getDefaultGravityForce() const;
	
	void applyMovement(float acc, float dec);
	
	float getMovementDir() const;
	
	void jump(float force, bool changeToJumpState = true);
	
	void enableJump();
	
	void wallJump();
	
	void enableWallJump();
	
	friend class PlayerStateMachine;
};

#endif