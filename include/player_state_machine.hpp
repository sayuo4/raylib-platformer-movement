#ifndef PLAYER_STATE_MACHINE_HPP
#define PLAYER_STATE_MACHINE_HPP

#include "player.hpp"
#include "utility.hpp"
#include <string>
#include <vector>

class PlayerState
{
protected:
	Signal<PlayerState*, std::string> stateTransition;
	Player* player = nullptr;

	PlayerState(std::string name);

	virtual void enter(std::string previousState);
	virtual void exit(std::string newState);
	virtual void update(float deltaTime);
	virtual void fixedUpdate(float deltaTime);

	void switchToState(std::string stateName);

public:
	const std::string name;

	friend class PlayerStateMachine;
};

class PlayerStateMachine : Object
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
	
	void update(float deltaTime) override;
	void fixedUpdate(float deltaTime) override;
};

#endif