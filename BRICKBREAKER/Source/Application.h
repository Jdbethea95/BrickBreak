#ifndef APPLICATION_H
#define APPLICATION_H

//include events
#include "Events/Playevents.h"
// Contains our global game settings
#include "GameConfig.h"
// Load all entities+prefabs used by the game 
#include "Entities/BulletData.h"
#include "Entities/PlayerData.h"
#include "Entities/EnemyData.h"
#include "Entities/BrickData.h"
#include "Entities/GemData.h"
#include "Entities//SballData.h"
#include "Components/Gameplay.h"
// Include all systems used by the game and their associated components
#include "Systems/PlayerLogic.h"
//#include "Systems/VulkanRendererLogic.h"
#include "Systems/renderer.h" //belongs to new renderer DX11. This is Causing A Linker Error LNK2005 already exists in Apllication.obj
#include "Systems/LevelLogic.h"
#include "Systems/PhysicsLogic.h"
#include "Systems/BulletLogic.h"
#include "Systems/EnemyLogic.h"
#include "Packet.h"


// Allocates and runs all sub-systems essential to operating the game
class Application 
{
	// gateware libs used to access operating system
	GW::SYSTEM::GWindow window; // gateware multi-platform window
	//GW::GRAPHICS::GVulkanSurface vulkan; // gateware vulkan API wrapper
	GW::GRAPHICS::GDirectX11Surface d3d11;
	GW::INPUT::GController gamePads; // controller support
	GW::INPUT::GInput immediateInput; // twitch keybaord/mouse
	GW::INPUT::GBufferedInput bufferedInput; // event keyboard/mouse
	GW::AUDIO::GAudio audioEngine; // can create music & sound effects
	// third-party gameplay & utility libraries
	std::shared_ptr<flecs::world> game; // ECS database for gameplay
	std::shared_ptr<GameConfig> gameConfig; // .ini file game settings
	// ECS Entities and Prefabs that need to be loaded
	//BBG::BulletData weapons;

	BBG::PlayerData players;
	BBG::EnemyData enemies;
	BBG::BrickData bricks;
	BBG::GemData gems;
	BBG::SballData balls;
	// specific ECS systems used to run the game
	BBG::PlayerLogic playerSystem;
	//BBG::VulkanRendererLogic vkRenderingSystem;
	BBG::LevelLogic levelSystem;
	BBG::ResetLogic resetSystem;
	BBG::PhysicsLogic physicsSystem;

	//BBG::BulletLogic bulletSystem;

	BBG::BallLogic ballSystem;
	BBG::BallData ball;

	BBG::EnemyLogic enemySystem;
	// EventGenerator for Game Events
	GW::CORE::GEventGenerator eventPusher;
	BBG::Packets collectionPack;
	Level_Data lvlData;
	std::vector<bool> levels;
	int levelindex = 0;

	bool reset = false;
	int currentLevel = 3;
	int currentScore = 0;
	int lifeScore = 3;
	int highScore = 0;
public:
	bool Init();
	bool Run();
	bool Shutdown();
private:
	bool InitWindow();
	bool InitLevelData();
	bool InitInput();
	bool InitAudio();
	bool InitGraphics();
	bool InitEntities(std::vector<BBG::GamePacket> strPkt); //starterpacket
	bool InitSystems(std::vector<BBG::GamePacket>* gamePkt, std::vector<BBG::GamePacket> strPkt, bool& reset); //gamepacket
	bool PauseSystems(bool fudge);
	bool GameLoop();
};

#endif 