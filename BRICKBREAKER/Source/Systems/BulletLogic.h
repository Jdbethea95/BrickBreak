// The Bullet system is responsible for inflicting damage and cleaning up bullets
#ifndef BALLLOGIC_H
#define BALLLOGIC_H


//#ifndef BULLETLOGIC_H
//#define BULLETLOGIC_H

// Contains our global game settings
#include "../GameConfig.h"
#include "../Entities/BulletData.h"

//(avoid name collisions)
namespace BBG
{
	class BallLogic 
	{

		// shared connection to the main ECS engine
		std::shared_ptr<flecs::world> game;
		// non-ownership handle to configuration settings
		std::weak_ptr<const GameConfig> gameConfig;
		GW::INPUT::GInput immediateInput;
		flecs::system ballSystem;
		std::vector<GamePacket>* gmpt;
		std::vector<bool>* lvls;
		bool down = false;
		bool d1 = false, d2 = false, d3 = false; //debug stuff
		bool gemPresent = false;
		bool timeForSball = false;
		int alienCount = 2;
		int currentLvl = 1;
		/// <summary>
		/// 
		/// </summary>
		/// <param name="game">: The Flecs world</param>
		/// <param name="zSize">: z range for current level</param>
		/// <param name="index">: index of current ball</param>
		/// <param name="toggle">: toggle ball on/true or off/false</param>
		/// <param name="vec">: Option var to be used for spawn pos when toggled on</param>
		GamePacket ActivateBalls(std::shared_ptr<flecs::world> game, int zSize, int index, bool toggle, GW::MATH2D::GVECTOR2F vec = GW::MATH2D::GVECTOR2F());
	public:
		// attach the required logic to the ECS 
		bool Init(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket>* gamepkt,
			GW::INPUT::GInput _immediateInput,
			GW::INPUT::GBufferedInput _bufferedInput,
			GW::INPUT::GController _controllerInput, bool& reset, std::vector<bool>* levels, int& lvlindex, int& hs, int& life);
		// control if the system is actively running
		bool Activate(bool runSystem);
		// release any resources allocated by the system
		bool Shutdown();


	};
	//class BulletLogic
	//{
	//	// shared connection to the main ECS engine
	//	std::shared_ptr<flecs::world> game;
	//	// non-ownership handle to configuration settings
	//	std::weak_ptr<const GameConfig> gameConfig;
	//public:
	//	// attach the required logic to the ECS 
	//	bool Init(std::shared_ptr<flecs::world> _game,
	//		std::weak_ptr<const GameConfig> _gameConfig);
	//	// control if the system is actively running
	//	bool Activate(bool runSystem);
	//	// release any resources allocated by the system
	//	bool Shutdown();
	//};

};

#endif // !BALLLOGIC_H