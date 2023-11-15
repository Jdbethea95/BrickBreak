#include <random>
#include "LevelLogic.h"
#include "../Components/Identification.h"
#include "../Components/Gameplay.h"
#include "../Components/Physics.h"
#include "../Entities/Prefabs.h"
#include "../Utils/Macros.h"

using namespace BBG; 

// Connects logic to traverse any players and allow a controller to manipulate them
bool BBG::LevelLogic::Init(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, GW::AUDIO::GAudio _audioEngine, std::vector<GamePacket> strPkt)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	audioEngine = _audioEngine;
	// create an asynchronus version of the world
	gameAsync = game->async_stage(); // just used for adding stuff, don't try to read data
	gameLock.Create();
	// Pull enemy Y start location from config file
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();
	float enemy1startY = (*readCfg).at("Enemy1").at("ystart").as<float>();
	float enemy1accmax = (*readCfg).at("Enemy1").at("accmax").as<float>();
	float enemy1accmin = (*readCfg).at("Enemy1").at("accmin").as<float>();
	// level one info
	float spawnDelay = (*readCfg).at("Level1").at("spawndelay").as<float>();
	int enemycount = 0;
	std::vector<GW::MATH2D::GVECTOR2F> vec;
	int gemCount = 0;
	flecs::entity backup;
	std::vector<flecs::entity> balls;
	int sballCount = 0; //the count of how many s-balls are active

	game.get()->component<Life>().set<Life>({ 3 });

	for (int i = 0; i < strPkt.size(); i++)
	{
		if (strPkt[i].name == "Container_Small")
		{
			GW::MATH2D::GRECTANGLE2F box;
			box.min = { -5.1, -3 };
			box.max = { 5.1, 3 };
			flecs::entity et2;
			if (RetreivePrefab("brick", et2)) {
				// you must ensure the async_stage is thread safe as it has no built-in synchronization
				gameLock.LockSyncWrite();
				// this method of using prefabs is pretty conveinent
				gameAsync.entity().is_a(et2)
					.set<WorldMatrix>({ strPkt[i].matrix })
					.set<ObjectID>({ i })
					.set<BoxCollider>({ box });
				std::cout << "brick created" << std::endl;
				// be sure to unlock when done so the main thread can safely merge the changes
				gameLock.UnlockSyncWrite();
			}
		}
		else if (strPkt[i].name == "Alien")
		{
			GW::MATH2D::GRECTANGLE2F box;
			box.min = { -2.5, -1.75 };
			box.max = { 2.5, 0.75 };
			flecs::entity et2;
			if (RetreivePrefab("enemy", et2)) {
				// you must ensure the async_stage is thread safe as it has no built-in synchronization
				gameLock.LockSyncWrite();
				// this method of using prefabs is pretty conveinent
				gameAsync.entity().is_a(et2)
					.set<WorldMatrix>({ strPkt[i].matrix })
					.set<ObjectID>({ i })
					.set<BoxCollider>({ box });
				std::cout << "enemy created" << std::endl;
				// be sure to unlock when done so the main thread can safely merge the changes
				gameLock.UnlockSyncWrite();
				enemycount++;
			}
		}
		else if (strPkt[i].name == "Crystal2")
		{
			std::string bloopFX = (*readCfg).at("Ball").at("bloopFX").as<std::string>();
			GW::AUDIO::GSound shoot;
			shoot.Create(bloopFX.c_str(), _audioEngine, 0.15f); // we need a global music & sfx volumes

			GW::MATH2D::GRECTANGLE2F box;
			box.min = { -1.5, -1.75 };
			box.max = { 1.5, 0.75 };
			flecs::entity et2;
			if (RetreivePrefab("gem", et2)) {
				// you must ensure the async_stage is thread safe as it has no built-in synchronization
				gameLock.LockSyncWrite();
				// this method of using prefabs is pretty conveinent
				auto save = gameAsync.entity().is_a(et2)
					.set<WorldMatrix>({ strPkt[i].matrix })
					.set<ObjectID>({ i })
					.set<BoxCollider>({ box })
					.set<ActiveGem>({ false })
					.set<GW::AUDIO::GSound>(shoot.Relinquish());
				std::cout << "gem created" << std::endl;
				// be sure to unlock when done so the main thread can safely merge the changes
				gameLock.UnlockSyncWrite();

				//may cause problems
				if (gemCount == 0)
				{
					backup = save;
					game.get()->component<GemCache>().set<GemCache>({ save, backup });
				}
				else
				{
					game.get()->component<GemCache>().set<GemCache>({ backup, save });
				}

			}

		}
		else if (strPkt[i].name == "Planet_11")
		{
			GW::MATH2D::GRECTANGLE2F top, bottom, left, right;
			top.min = { -2.15f, 0.3f };//bc.top.min.x = -2.15f; bc.top.min.y = 0.3f; //-.5 .25
			top.max = { 2.15f, 2.3f };//bc.top.max.x = 2.15f; bc.top.max.y = 2.3f; //.5 .5
			bottom.min = { -2.15f, -2.3f };////bottom rect
			bottom.max = { 2.15f, 0.3f };//bc.bottom.min.x = -2.15f; bc.bottom.min.y = -2.3f; //-.5 -.5
			left.min = { -2.3f, -2.15f };//bc.bottom.max.x = 2.15f; bc.bottom.max.y = 0.3f; //.5 -.25
			left.max = { 0.3f, 2.15f };////left rect
			right.min = { 0.3f, -2.15f };//bc.left.min.x = -2.3f; bc.left.min.y = -2.15f; //-.5 -.5
			right.max = { 2.3f, 2.15f };//bc.left.max.x = 0.0f; bc.left.max.y = 2.15f; //-.25 .5
			////right rect
			//bc.right.min.x = 0.0f; bc.right.min.y = -2.15f; //.25 -.5
			//bc.right.max.x = 2.3f; bc.right.max.y = 2.15f; //.5 .5
			flecs::entity et2;
			if (RetreivePrefab("ball", et2)) {
				// you must ensure the async_stage is thread safe as it has no built-in synchronization
				gameLock.LockSyncWrite();
				// this method of using prefabs is pretty conveinent
				auto save = gameAsync.entity().is_a(et2)
					.set<WorldMatrix>({ strPkt[i].matrix })
					.set<ObjectID>({ i })
					.set<Velocity>({ 0.0f, 0.0f, 0.05f })
					.set<BallColliders>({ top, bottom, left, right })
					.set<SballID>({ sballCount })
					.set<ActiveBall>({ false });
				std::cout << "Sball created" << std::endl;
				// be sure to unlock when done so the main thread can safely merge the changes
				gameLock.UnlockSyncWrite();
				balls.push_back(save);
				sballCount++;
			}

		}
		else if (strPkt[i].name == "Grass_1")
		{
		GW::MATH2D::GRECTANGLE2F box;
		box.min = { -2.5, -1.75 };
		box.max = { 2.5, 0.75 };
		flecs::entity et2;
		if (RetreivePrefab("POS", et2)) {
			// you must ensure the async_stage is thread safe as it has no built-in synchronization
			gameLock.LockSyncWrite();
			// this method of using prefabs is pretty conveinent
			gameAsync.entity().is_a(et2)
				.set<WorldMatrix>({ strPkt[i].matrix })
				.set<ObjectID>({ i })
				.set<BoxCollider>({ box });
			std::cout << "POS created" << std::endl;
			// be sure to unlock when done so the main thread can safely merge the changes
			GW::MATH2D::GVECTOR2F penny; 
			penny.x = strPkt[i].matrix.row4.x; penny.y = strPkt[i].matrix.row4.y;
			vec.push_back(penny);
			gameLock.UnlockSyncWrite();
			
		}
		}
	}
	int size = balls.size(); //to go from size_t to int, because component wont covnert.
	game.get()->component<BallArray>().set<BallArray>({ balls });
	game.get()->component<ActiveSBALLS>().set<ActiveSBALLS>({ 0 });
	game.get()->component<EnemyCount>().set<EnemyCount>({ 2 });
	game.get()->component<lvl1>().set<lvl1>({ vec[0]});
	game.get()->component<lvl2>().set<lvl2>({ vec[1] });
	game.get()->component<lvl3>().set<lvl3>({ vec[2] });
	game.get()->component<LevelUp>().set<LevelUp>({ false });
	 //dont judge me
	//.override<WorldMatrix>()
	//.override<BoxCollider>()
	//.override<Brick>() // Tag this prefab as an enemy (for queries/systems)
	//.override<Collidable>();


// create a system the runs at the end of the frame only once to merge async changes
	struct LevelSystem {}; // local definition so we control iteration counts
	game->entity("Level System").add<LevelSystem>();
	// only happens once per frame at the very start of the frame
	game->system<LevelSystem>().kind(flecs::OnLoad) // first defined phase
		.each([this](flecs::entity e, LevelSystem& s) {
		// merge any waiting changes from the last frame that happened on other threads
		gameLock.LockSyncWrite();
		gameAsync.merge();
		gameLock.UnlockSyncWrite();
			});

	// Load and play level one's music
	currentTrack.Create("../Music/Level 1 Ambience.wav", audioEngine, 0.15f);
	currentTrack.Play(false);

	return true;
}

// Free any resources used to run this system
bool BBG::LevelLogic::Shutdown()
{

	timedEvents = nullptr; // stop adding enemies
	gameAsync.merge(); // get rid of any remaining commands
	game->entity("Level System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}

// Toggle if a system's Logic is actively running
bool BBG::LevelLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Level System").enable();
	}
	else {
		game->entity("Level System").disable();
	}
	return false;
}

// **** SAMPLE OF MULTI_THREADED USE ****
//flecs::world world; // main world
//flecs::world async_stage = world.async_stage();
//
//// From thread
//lock(async_stage_lock);
//flecs::entity e = async_stage.entity().child_of(parent)...
//unlock(async_stage_lock);
//
//// From main thread, periodic
//lock(async_stage_lock);
//async_stage.merge(); // merge all commands to main world
//unlock(async_stage_lock);

bool BBG::ResetLogic::Init(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket>* gamepkt, std::vector<GamePacket> strpkt, GW::INPUT::GInput _immediateInput, GW::INPUT::GBufferedInput _bufferedInput, GW::INPUT::GController _controllerInput, bool& reset)
{
	game = _game;
	gameConfig = _gameConfig;
	immediateInput = _immediateInput;
	gmpt = gamepkt;
	stpt = strpkt;
	lvl = 0;
	present = false;
	resetSystem = game->system<GameObject*, WorldMatrix*, ObjectID*>("Reset System").each([&](flecs::entity e, GameObject* go, WorldMatrix* wm, ObjectID* id)
		{
			
			if (reset)
			{
				present = false;
				for (size_t i = 0; i < stpt.size(); i++)
				{
					if (id == nullptr)
						break;
						
						
						gmpt->push_back(GamePacket(stpt[i]));

						if (id->value == stpt[i].objectID)
							wm->value.row4 = stpt[i].matrix.row4;
						
					
				}

			}
		});
	return true;
}

bool BBG::ResetLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Reset System").enable();
	}
	else {
		game->entity("Reset System").disable();
	}
	return false;
}

bool BBG::ResetLogic::Shutdown()
{
	game->entity("Reset System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}
