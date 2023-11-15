#include "GemData.h"
#include "../Components/Identification.h"
#include "../Components/visuals.h"
#include "../Components/Physics.h"
#include "../Entities/Prefabs.h"
#include "../Components/Gameplay.h"


bool BBG::GemData::Load(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket> strpkt)
{
	// Grab init settings for bricks
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();

	// Create prefab for lazer weapon
	// attributes
	int health = (*readCfg).at("Enemy1").at("health").as<int>();
	//Collider Polygon Dimensions
	

	// default projectile orientation & scale
	GW::MATH2D::GMATRIX2F world;

	// add prefab to ECS
	auto gemPrefab = _game->prefab("gem")
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<WorldMatrix>()
		.override<ObjectID>()
		.override<BoxCollider>()
		.override<ActiveGem>()
		.override<Gem>() // Tag this prefab as a gem (for queries/systems)
		.override<Collidable>(); // can be collided with

	// register this prefab by name so other systems can use it
	RegisterPrefab("gem", gemPrefab);
	return true;
}

bool BBG::GemData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all players
	_game->defer_begin(); // required when removing while iterating!
	_game->each([](flecs::entity e, Player&) {
		e.destruct(); // destroy this entitiy (happens at frame end)
		});
	_game->defer_end(); // required when removing while iterating!

	return true;
}