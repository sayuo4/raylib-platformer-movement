#ifndef PLAYER_STATES_HPP
#define PLAYER_STATES_HPP

#include "player_state_machine.hpp"
#include <string>

class PlayerIdleState : public PlayerState
{
private:
	// this is a comment from 3qrooooooooooooooooooooooooooooooooooooooooooooooooooob.
	void fixedUpdate(float deltaTime) override;

public:
	PlayerIdleState();
};

class PlayerRunningState : public PlayerState
{
private:
	void fixedUpdate(float deltaTime) override;

public:
	PlayerRunningState();
};

class PlayerLandingState : public PlayerState
{
private:
	void enter(std::string) override;

public:
	PlayerLandingState();
};

class PlayerFallingState : public PlayerState
{
private:
	void fixedUpdate(float deltaTime) override;

public:
	PlayerFallingState();
};

class PlayerWallSlidingState : public PlayerState
{
private:
	void fixedUpdate(float deltaTime) override;

public:
	PlayerWallSlidingState();
};

class PlayerJumpingState : public PlayerState
{
private:
	void fixedUpdate(float deltaTime) override;

public:
	PlayerJumpingState();
};

class PlayerWallJumpingState: public PlayerState
{
private:
	void fixedUpdate(float deltaTime) override;

public:
	PlayerWallJumpingState();
};

class PlayerAirborneState : public PlayerState
{
private:
	void enter(std::string) override;

public:
	PlayerAirborneState();
};

#endif