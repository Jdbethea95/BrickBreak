// The level system is responsible for transitioning the various levels in the game
#ifndef PHYSICSLOGIC_H
#define PHYSICSLOGIC_H

// Contains our global game settings
#include "../GameConfig.h"
#include "../Packet.h"
#include "../Components/Physics.h"

// BBG (avoid name collisions)
namespace BBG
{
	class PhysicsLogic
	{
		// shared connection to the main ECS engine
		std::shared_ptr<flecs::world> game;

		// non-ownership handle to configuration settings
		std::weak_ptr<const GameConfig> gameConfig;

		std::vector<GamePacket>* gamePkt;

		// used to cache collision queries //Collidable, Position, Orientation
		flecs::query<Collidable, WorldMatrix, BoxCollider > queryCache;
		flecs::query<Collidable, WorldMatrix, BallColliders> ballCache;
		// defines what to be tested
		static constexpr unsigned polysize = 4;
		struct SHAPE 
		{
			GW::MATH2D::GVECTOR2F poly[polysize];
			flecs::entity owner;
		};

		struct RECT
		{
			GW::MATH2D::GRECTANGLE2F rect;
			flecs::entity owner;
		};

		// vector used to save/cache all active collidables
		std::vector<SHAPE> testCache;
		std::vector<RECT> ballColliders;
		std::vector<RECT> brickColliders;

	public:

		// attach the required logic to the ECS 
		bool Init(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket>* gamepkt, GW::AUDIO::GAudio _audioEngine);

		// control if the system is actively running
		bool Activate(bool runSystem);

		// release any resources allocated by the system
		bool Shutdown();
	};

};

#endif