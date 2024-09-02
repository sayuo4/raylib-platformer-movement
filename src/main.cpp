#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

#include "raylib-cpp.hpp"
#include "utility.hpp"
#include "input_manager.hpp"
#include "object.hpp"
#include "physics_object.hpp"
#include "moving_object.hpp"
#include "solid_object.hpp"
#include "player.hpp"
#include "player_state_machine.hpp"
#include "player_states.hpp"

#define DEBUG


int main()
{
	raylib::Window window {800, 600, "Player Movement"};
	window.SetTargetFPS(60);

	Player* player = new Player(64.0f * 3.0f, 200.0f, 56.0f, 96.0f);

	PlayerStateMachine playerStateMachine = PlayerStateMachine(player);

	PlayerIdleState* playerIdleState = new PlayerIdleState;
	PlayerRunningState* playerRunningState = new PlayerRunningState;
	PlayerLandingState* playerLandingState = new PlayerLandingState;
	PlayerFallingState* playerFallingState = new PlayerFallingState;
	PlayerJumpingState* playerJumpingState = new PlayerJumpingState;
	PlayerWallJumpingState* playerWallJumpingState = new PlayerWallJumpingState; 
	PlayerAirborneState* playerAirborneState = new PlayerAirborneState;

	playerStateMachine.addState(playerIdleState)
		.addState(playerRunningState)
		.addState(playerJumpingState)
		.addState(playerFallingState)
		.addState(playerAirborneState)
		.addState(playerLandingState)
		.addState(playerWallJumpingState);

	playerStateMachine.setActiveState(playerFallingState);


	SolidObject* ground = new SolidObject(
		0.0f,
		window.GetSize().y - 64.0f,
		window.GetSize().x,
		64.0f
	);

	SolidObject* rightWall = new SolidObject(
		window.GetSize().x - 64.0f,
		0.0f,
		64.0f,
		window.GetSize().y
	);

	SolidObject* leftWall = new SolidObject(
		rightWall->rect.GetPosition().x - (64.0f * 4.0f),
		0.0f,
		64.0f,
		window.GetSize().y - (64.0f * 3.0f)
	);

	while (!window.ShouldClose())
	{
		Object::updateObjects();

		window.BeginDrawing();
		window.ClearBackground(GRAY);

#ifdef DEBUG
		raylib::DrawText("Player State: " + playerStateMachine.getActiveState()->name, 16, 16, 20, BLACK);
		raylib::DrawText("Player Collision Count: " + std::to_string(player->collisionList.size()), 16, 40, 20, BLACK);
		raylib::DrawText("FPS: " + std::to_string(GetFPS()), 16, 64, 20, BLACK);
#endif

		player->rect.Draw(WHITE);
		ground->rect.Draw(BLACK);
		rightWall->rect.Draw(BLACK);
		leftWall->rect.Draw(BLACK);

		window.EndDrawing();
	}
}
