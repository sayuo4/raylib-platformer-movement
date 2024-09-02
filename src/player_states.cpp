#include "player_states.hpp"
#include <iostream>


void PlayerIdleState::fixedUpdate(float deltaTime)
{
	player->applyGravity(deltaTime);
	player->applyMovement(player->RUNNING_ACC, player->RUNNING_DEC);

	player->move();
	player->enableJump();

	if (!player->isOnFloor) switchToState("PlayerAirborneState");
	else if (player->velocity.x) switchToState("PlayerRunningState");
}

PlayerIdleState::PlayerIdleState() : PlayerState("PlayerIdleState") {}


void PlayerRunningState::fixedUpdate(float deltaTime)
{
	player->applyGravity(deltaTime);
	player->applyMovement(player->RUNNING_ACC, player->RUNNING_DEC);

	player->move();
	player->enableJump();

	if (!player->isOnFloor)
		switchToState("PlayerAirborneState");
	
	else if (!player->velocity.x and !player->getHorizontalInput())
		switchToState("PlayerIdleState");
}

PlayerRunningState::PlayerRunningState() : PlayerState("PlayerRunningState") {}


void PlayerLandingState::enter(std::string)
{
	if (!player->velocity.x)
	{
		switchToState("PlayerIdleState");
		return;
	}

	switchToState("PlayerRunningState");
}

PlayerLandingState::PlayerLandingState() : PlayerState("PlayerLandingState") {}


void PlayerFallingState::fixedUpdate(float deltaTime)
{
	player->applyGravity(deltaTime);
	player->applyMovement(player->FALLING_ACC, player->FALLING_DEC);

	player->move();

	if (player->isOnWall)
		player->enableWallJump();

	if (player->isOnFloor)
		switchToState("PlayerLandingState");
	
	else if (player->velocity.y < 0)
		switchToState("PlayerJumpingState");
}

PlayerFallingState::PlayerFallingState() : PlayerState("PlayerFallingState") {}


void PlayerWallSlidingState::fixedUpdate(float deltaTime)
{

}

PlayerWallSlidingState::PlayerWallSlidingState() : PlayerState("PlayerWallSlidingState") {}


void PlayerJumpingState::fixedUpdate(float deltaTime)
{
	player->applyGravity(deltaTime);
	player->applyMovement(player->JUMPING_ACC, player->JUMPING_DEC);

	player->move();

	if (player->isOnWall) player->enableWallJump();

	if (player->velocity.y >= 0) switchToState("PlayerFallingState");
}

PlayerJumpingState::PlayerJumpingState() : PlayerState("PlayerJumpingState") {}


void PlayerWallJumpingState::fixedUpdate(float deltaTime)
{
	player->applyGravity(deltaTime);

	const float DEC = (player->getHorizontalInput() == player->wallDir) ? player->WALL_JUMPING_TOWARDS_WALL_DEC : player->WALL_JUMPING_DEC;
	player->applyMovement(player->WALL_JUMPING_ACC, DEC);

	player->move();

	if (player->isOnWall) player->enableWallJump();

	if (player->velocity.y >= 0) switchToState("PlayerFallingState");
}

PlayerWallJumpingState::PlayerWallJumpingState() : PlayerState("PlayerWallJumpingState") {}


void PlayerAirborneState::enter(std::string)
{
	if (player->velocity.y >= 0)
	{
		switchToState("PlayerFallingState");
		return;
	}

	switchToState("PlayerJumpingState");
}

PlayerAirborneState::PlayerAirborneState() : PlayerState("PlayerAirborneState") {}
