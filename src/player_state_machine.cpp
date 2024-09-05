#include "player_state_machine.hpp"
#include <iostream>
#include <functional>

PlayerState::PlayerState(std::string name) : name(name) {}

void PlayerState::enter(std::string previousState) {}
void PlayerState::exit(std::string newState) {}

void PlayerState::update(float deltaTime) {}

void PlayerState::fixedUpdate(float deltaTime) {}

void PlayerState::switchToState(std::string stateName)
{
	stateTransition.emit(this, stateName);
}


void PlayerStateMachine::stateTransition(PlayerState* currentState, std::string state_name)
{
	if (currentState == activeState)
		forceStateTransition(state_name);
}

void PlayerStateMachine::forceStateTransition(std::string state_name)
{
	for (auto& state : states)
	{
		if (state->name == state_name)
		{
			setActiveState(state);
			return;
		}
	}

	std::cerr << "Can't find state: '" << state_name << "' in player state machine\n";
}

PlayerStateMachine::PlayerStateMachine(Player* player) : player(player)
{
	player->forceStateTransition.connect(std::bind(&PlayerStateMachine::forceStateTransition, this, std::placeholders::_1));
}

void PlayerStateMachine::setActiveState(PlayerState* newState)
{
	PlayerState* previousState = activeState;
	
	if (newState == activeState)
		return;

	activeState = newState;

	if (previousState)
		previousState->exit(newState ? newState->name : "");

	if (newState)
		newState->enter(previousState ? previousState->name : "");
}

PlayerState* PlayerStateMachine::getActiveState()
{
	return activeState;
}

PlayerStateMachine& PlayerStateMachine::addState(PlayerState* state)
{
	states.push_back(state);
	state->stateTransition.connect(std::bind(&PlayerStateMachine::stateTransition, this, std::placeholders::_1, std::placeholders::_2));
	state->player = player;

	return *this;
}

void PlayerStateMachine::update(float deltaTime)
{
	if (activeState)
		activeState->update(deltaTime);
}

void PlayerStateMachine::fixedUpdate(float deltaTime)
{
	if (activeState)
		activeState->fixedUpdate(deltaTime);
}