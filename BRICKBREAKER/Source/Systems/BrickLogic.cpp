#include <random>
#include "BrickLogic.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "../Components/Gameplay.h"
#include "../Events/Playevents.h"

using namespace BBG; 

// Connects logic to traverse any players and allow a controller to manipulate them
bool BBG::BrickLogic::Init(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	GW::CORE::GEventGenerator _eventPusher)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	eventPusher = _eventPusher;

	// destroy any bullets that have the CollidedWith relationship
	game->system<Enemy, Health>("Brick System")
		.each([this](flecs::entity e, Enemy, Health& h) {
		// if you have no health left be destroyed
		if (e.get<Health>()->value <= 0) {
			// play explode sound
			e.destruct();
			BBG::PLAY_EVENT_DATA x;
			GW::GEvent explode;
			explode.Write(BBG::PLAY_EVENT::ENEMY_DESTROYED, x);
			eventPusher.Push(explode);
		}
			});

	return true;
}

// Free any resources used to run this system
bool BBG::BrickLogic::Shutdown()
{
	game->entity("Brick System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}

// Toggle if a system's Logic is actively running
bool BBG::BrickLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Brick System").enable();
	}
	else {
		game->entity("Brick System").disable();
	}
	return false;
}