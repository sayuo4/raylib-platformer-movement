#ifndef PLAYER_STATES_HPP
#define PLAYER_STATES_HPP

#include <string>

#include "player_state_machine.hpp"


class PlayerIdleState : public PlayerState
{
private:
	void update() override;

public:
	PlayerIdleState();
};

class PlayerRunningState : public PlayerState
{
private:
	void update() override;

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
	void update() override;

public:
	PlayerFallingState();
};

class PlayerWallSlidingState : public PlayerState
{
private:
	void update() override;

public:
	PlayerWallSlidingState();
};

class PlayerJumpingState : public PlayerState
{
private:
	void update() override;

public:
	PlayerJumpingState();
};

class PlayerWallJumpingState: public PlayerState
{
private:
	void update() override;

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