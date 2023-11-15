#include "BrickData.h"
#include "../Components/Identification.h"
#include "../Components/visuals.h"
#include "../Components/Physics.h"
#include "../Entities/Prefabs.h"
#include "../Components/Gameplay.h"


bool BBG::BrickData::Load(std::shared_ptr<flecs::world> _game,
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
	auto brickPrefab = _game->prefab("brick")
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<WorldMatrix>()
		.override<ObjectID>()
		.override<BoxCollider>()
		.override<Brick>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>()
		.override<GameObject>(); // can be collided with

	// register this prefab by name so other systems can use it
	RegisterPrefab("brick", brickPrefab);

	auto enemyPrefab = _game->prefab("enemy")
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<WorldMatrix>()
		.override<BoxCollider>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>()
		.override<GameObject>(); // can be collided with

	// register this prefab by name so other systems can use it
	RegisterPrefab("enemy", enemyPrefab);

	// register this prefab by name so other systems can use it
	RegisterPrefab("brick", brickPrefab);

	auto posPrefab = _game->prefab("POS")
		// .override<> ensures a component is unique to each entity created from a prefab
		.set_override<Health>({ health })
		.override<WorldMatrix>()
		.override<BoxCollider>()
		.override<Enemy>() // Tag this prefab as an enemy (for queries/systems)
		.override<Collidable>()
		.override<LevelPOS>(); // can be collided with

	// register this prefab by name so other systems can use it
	RegisterPrefab("POS", posPrefab);

	return true;
}

bool BBG::BrickData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all players
	_game->defer_begin(); // required when removing while iterating!
	_game->each([](flecs::entity e, Player&) {
		e.destruct(); // destroy this entitiy (happens at frame end)
		});
	_game->defer_end(); // required when removing while iterating!

	return true;
}