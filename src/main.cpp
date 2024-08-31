#include <Functions.hpp>
#include <iostream>
#include <raylib.h>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

#include "raylib-cpp.hpp"
#include "utility.hpp"
#include "physics_system.hpp"
#include "physics_bodies.hpp"
#include "player.hpp"
#include "player_state_machine.hpp"
#include "player_states.hpp"

#define DEBUG


int main()
{
	raylib::Window window {800, 600, "Player Movement"};
	window.SetTargetFPS(60);

	PhysicsSystem* physicsSystem = new PhysicsSystem;

	Player* player = new Player(CollisionRect(raylib::Vector2(64.0 * 3.0, 200.0), raylib::Vector2(56.0, 96.0)), physicsSystem);
	
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
		.addState(playerLandingState)
		.addState(playerJumpingState)
		.addState(playerFallingState)
		.addState(playerAirborneState)
		.addState(playerWallJumpingState);

	playerStateMachine.setActiveState(playerFallingState);


	StaticBody* ground = new StaticBody(
		CollisionRect(0.0, static_cast<float>(window.GetHeight() - 64), static_cast<float>(window.GetWidth()), 64.0),
		physicsSystem
	);

	StaticBody* firstWall = new StaticBody(
		CollisionRect(static_cast<float>(window.GetWidth() - 64), 0.0, 64.0, static_cast<float>(window.GetHeight())),
		physicsSystem
	);

	while (!window.ShouldClose())
	{
		player->update();
		playerStateMachine.update();

		// std::cout << player->collisionList.size() << '\n';
		// CollisionInfo* testMove = player->testMove(raylib::Vector2(0.0));
		// std::cout << testMove->intersection.x << " " << testMove->intersection.y << " " << testMove->intersection.width << " " << testMove->intersection.height << " " << '\n';

		window.BeginDrawing();
		window.ClearBackground(GRAY);

#ifdef DEBUG
		raylib::DrawText(playerStateMachine.getActiveState()->name, 32, 32, 24, BLACK);
		raylib::DrawText(std::to_string(player->collisionList.size()), 32, 64, 24, BLACK);
#endif

		player->collision.rect.Draw(WHITE);
		ground->collision.rect.Draw(BLACK);
		firstWall->collision.rect.Draw(BLACK);
		// DrawRectangle(testMove->intersection.x, testMove->intersection.y, testMove->intersection.width, testMove->intersection.height, RED);
		// if (testMove) delete testMove;

		window.EndDrawing();
	}
}
