#ifndef PLAYER_STATE_MACHINE_HPP
#define PLAYER_STATE_MACHINE_HPP

#include <string>
#include <vector>

#include "utility.hpp"
#include "player.hpp"

class PlayerState
{
protected:
	Signal<PlayerState*, std::string> stateTransition;
	Player* player = nullptr;

	PlayerState(std::string name);

	virtual void enter(std::string previousState);
	virtual void exit(std::string newState);
	virtual void update();

	void switchToState(std::string stateName);

public:
	const std::string name;

	friend class PlayerStateMachine;
};

class PlayerStateMachine
{
private:
	Player* player;
	std::vector<PlayerState*> states;
	PlayerState* activeState = nullptr;
	
	void stateTransition(PlayerState* currentState, std::string state_name);

	void forceStateTransition(std::string state_name);

public:
	PlayerStateMachine(Player* player);
	
	void setActiveState(PlayerState* newState);
	
	PlayerState* getActiveState();

	PlayerStateMachine& addState(PlayerState* state);
	
	void update();
};

#endif