// This class creates all types of enemy prefabs
#ifndef SBALLDATA_H
#define SBALLDATA_H

// Contains our global game settings
#include "../GameConfig.h"
#include "../Packet.h"

// BBG (avoid name collisions)
namespace BBG
{
	class SballData
	{
	public:
		// Load required entities and/or prefabs into the ECS 
		bool Load(std::shared_ptr<flecs::world> _game,
			std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket> strpkt);
		// Unload the entities/prefabs from the ECS
		bool Unload(std::shared_ptr<flecs::world> _game);
	};

};

#endif
