#include "BulletData.h"
#include "../Components/Identification.h"
#include "../Components/Visuals.h"
#include "../Components/Physics.h"
#include "Prefabs.h"
#include "../Components/Gameplay.h"


//bool BBG::BulletData::Load(	std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, GW::AUDIO::GAudio _audioEngine)
//{
//	// Grab init settings for players
//	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();
//	
//	// Create prefab for lazer weapon
//	// color
//
//	float red = (*readCfg).at("Lazers").at("red").as<float>();
//	float green = (*readCfg).at("Lazers").at("green").as<float>();
//	float blue = (*readCfg).at("Lazers").at("blue").as<float>();
//
//	// other attributes
//	float speed = (*readCfg).at("Lazers").at("speed").as<float>();
//	float xscale = (*readCfg).at("Lazers").at("xscale").as<float>();
//	float yscale = (*readCfg).at("Lazers").at("yscale").as<float>();
//	int dmg = (*readCfg).at("Lazers").at("damage").as<int>();
//	int pcount = (*readCfg).at("Lazers").at("projectiles").as<int>();
//	float frate = (*readCfg).at("Lazers").at("firerate").as<float>();
//	std::string fireFX = (*readCfg).at("Lazers").at("fireFX").as<std::string>();
//	// default projectile scale
//	GW::MATH2D::GMATRIX2F world;
//	GW::MATH2D::GMatrix2D::Scale2F(GW::MATH2D::GIdentityMatrix2F, 
//	GW::MATH2D::GVECTOR2F{ xscale, yscale }, world);
//	// Load sound effect used by this bullet prefab
//	GW::AUDIO::GSound shoot;
//	shoot.Create(fireFX.c_str(), _audioEngine, 0.15f); // we need a global music & sfx volumes
//	// add prefab to ECS
//	auto lazerPrefab = _game->prefab()
//		// .set<> in a prefab means components are shared (instanced)
//		.set<Material>({ red, green, blue })
//		.set<Orientation>({ world })
//		.set<Acceleration>({ 0, 0 })
//		.set<Velocity>({ 0, speed })
//		.set<GW::AUDIO::GSound>(shoot.Relinquish())
//		// .override<> ensures a component is unique to each entity created from a prefab 
//		.set_override<Damage>({ dmg })
//		//.set_override<ChargedShot>({ 2 })
//		.override<Position>()
//		.override<Bullet>() // Tag this prefab as a bullet (for queries/systems)
//		.override<Collidable>(); // can be collided with
//
//	// register this prefab by name so other systems can use it
//	RegisterPrefab("Lazer Bullet", lazerPrefab);
//
//	return true;
//}
//
//bool BBG::BulletData::Unload(std::shared_ptr<flecs::world> _game)
//{
//	// remove all bullets and their prefabs
//	_game->defer_begin(); // required when removing while iterating!
//	_game->each([](flecs::entity e, Bullet&) {
//		e.destruct(); // destroy this entitiy (happens at frame end)
//	});
//	_game->defer_end(); // required when removing while iterating!
//
//	// unregister this prefab by name
//	UnregisterPrefab("Lazer Bullet");
//
//	return true;
//}

bool BBG::BallData::Load(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket> strpkt, GW::AUDIO::GAudio _audioEngine)
{
	// Grab init settings for players
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();

	// Create prefab for Ball 
	float xstart = 0;//(*readCfg).at("Ball").at("xstart").as<float>();
	float ystart = 0; //(*readCfg).at("Ball").at("ystart").as<float>();

	// other attributes
	float speed = 0; //(*readCfg).at("Ball").at("speed").as<float>();
	float gravity = 0; //(*readCfg).at("Ball").at("speed").as<float>();

	float xscale = 0; //(*readCfg).at("Ball").at("xscale").as<float>();
	float yscale = 0; //(*readCfg).at("Ball").at("yscale").as<float>();
	float zscale = 0; //(*readCfg).at("Ball").at("yscale").as<float>();

	int dmg = 0; //(*readCfg).at("Ball").at("damage").as<int>();
	int pcount = 0; //(*readCfg).at("Ball").at("projectiles").as<int>();
	float frate = 0; //(*readCfg).at("Ball").at("firerate").as<float>();

	// color
	float red = 0; //(*readCfg).at("Ball").at("red").as<float>();
	float green = 0; //(*readCfg).at("Ball").at("green").as<float>();
	float blue = 0; //(*readCfg).at("Ball").at("blue").as<float>();
	std::string fireFX = (*readCfg).at("Ball").at("fireFX").as<std::string>();
	std::string loseFX = (*readCfg).at("Ball").at("loseFX").as<std::string>();
	std::string winFX = (*readCfg).at("Ball").at("fireFX").as<std::string>();

	// default projectile scale
	GW::MATH2D::GMATRIX2F world;
    GW::MATH2D::GMatrix2D::Scale2F(GW::MATH2D::GIdentityMatrix2F, GW::MATH2D::GVECTOR2F{ xscale, yscale }, world);

	// Load sound effect used by this ball 
	GW::AUDIO::GSound shoot;
	GW::AUDIO::GSound shoot2;
	GW::AUDIO::GSound shoot3;
	shoot.Create(fireFX.c_str(), _audioEngine, 0.15f); // we need a global music & sfx volumes
	shoot2.Create(loseFX.c_str(), _audioEngine, 0.15f);
	shoot3.Create(winFX.c_str(), _audioEngine, 0.15f);

	GW::MATH::GMATRIXF holder;
	int ID;

	// Create Ball
	_game->entity("Ball").set([&](Orientation& o, Material& m, ControllerID& c, WorldMatrix& wm, ObjectID& oID, ActiveBall& bl, BallColliders& bc, Velocity& vel, SOUNDS& snd)
		{
			c = { 0 };
			m = { red, green, blue };
			bl = { false };
			o = { GW::MATH2D::GIdentityMatrix2F };
			snd.hit = shoot.Relinquish(); //.set<GW::AUDIO::GSound>(shoot.Relinquish())
			snd.lose = shoot2.Relinquish();
			vel.value = { 0,0 }; vel.speed = 0.02f;
			GW::MATH2D::GMatrix2D::Scale2F(o.value, GW::MATH2D::GVECTOR2F{ xscale, yscale }, o.value);
			
			//for loop with if statement looking for name of player object.
			for (size_t i = 0; i < strpkt.size(); i++)
			{
				if (strpkt[i].name == "Planet_1") //strpkt[i].name == "Column"
				{
					wm = { strpkt[i].matrix };
					oID = { strpkt[i].objectID };
					holder = strpkt[i].matrix;
					ID = strpkt[i].objectID;
					//Debug Info, prints to console.
					std::cout << "(" << strpkt[i].matrix.row4.x << ", " << strpkt[i].matrix.row4.y << ", " << strpkt[i].matrix.row4.z << ")" << std::endl;
					std::cout << i << " : " << strpkt[i].objectID << " : " << strpkt[i].name << " : " << "BallData" << std::endl;
				}
			}


			//SETTING UP BALL COLLIDERS T/B/L/R
			//top rect
			bc.top.min.x = -2.15f; bc.top.min.y = 0.3f; //-.5 .25
			bc.top.max.x = 2.15f; bc.top.max.y = 2.3f; //.5 .5
			//bottom rect
			bc.bottom.min.x = -2.15f; bc.bottom.min.y = -2.3f; //-.5 -.5
			bc.bottom.max.x = 2.15f; bc.bottom.max.y = 0.3f; //.5 -.25
			//left rect
			bc.left.min.x = -2.3f; bc.left.min.y = -2.15f; //-.5 -.5
			bc.left.max.x = 0.0f; bc.left.max.y = 2.15f; //-.25 .5
			//right rect
			bc.right.min.x = 0.0f; bc.right.min.y = -2.15f; //.25 -.5
			bc.right.max.x = 2.3f; bc.right.max.y = 2.15f; //.5 .5
			

	}).add<Ball>().add<Collidable>().add<GameObject>();

	// add prefab to ECS


	return true;
}

bool BBG::BallData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all bullets and their prefabs
	_game->defer_begin(); // required when removing while iterating!
	_game->each([](flecs::entity e, Ball&) { e.destruct(); }); // destroy this entitiy (happens at frame end)
	_game->defer_end(); // required when removing while iterating!


	// unregister this prefab by name
	UnregisterPrefab("Player Ball");

	return true;
}

