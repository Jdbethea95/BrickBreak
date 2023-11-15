#include "PlayerData.h"
#include "../Components/Identification.h"
#include "../Components/Visuals.h"
#include "../Components/Physics.h"
#include "../Components/Gameplay.h"
#include "Prefabs.h"


bool BBG::PlayerData::Load( std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket> strpkt, GW::AUDIO::GAudio _audioEngine)
{
	// Grab init settings for players
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();
	// color
	float red = (*readCfg).at("Player1").at("red").as<float>();
	float green = (*readCfg).at("Player1").at("green").as<float>();
	float blue = (*readCfg).at("Player1").at("blue").as<float>();
	// start position
	float xstart = (*readCfg).at("Player1").at("xstart").as<float>();
	float ystart = (*readCfg).at("Player1").at("ystart").as<float>();
	float scale = (*readCfg).at("Player1").at("scale").as<float>();

	// Create Player One
	_game->entity("Player One")
	.set([&](Position& p, Orientation& o, Material& m, ControllerID& c, WorldMatrix& wm, ObjectID& oID, BoxCollider& box, ProgressLvl& prg, Health& h)
		{
		c = { 0 };
		p = { xstart, ystart };
		m = { red, green, blue };
		o = { GW::MATH2D::GIdentityMatrix2F };
		h = { 0 };
		prg = { false };
		GW::MATH2D::GMatrix2D::Scale2F(o.value, GW::MATH2D::GVECTOR2F{ scale, scale }, o.value);
		//for loop with if statement looking for name of player object.
		for (size_t i = 0; i < strpkt.size(); i++)
		{
			if (strpkt[i].name == "Column") //strpkt[i].name == "Column"
			{
				wm = { strpkt[i].matrix };
				oID = { strpkt[i].objectID };
				//Debug Info, prints to console.
				std::cout << "(" << strpkt[i].matrix.row4.x << ", " << strpkt[i].matrix.row4.y << ", " << strpkt[i].matrix.row4.z << ")" << std::endl;
				std::cout << i << " : " << strpkt[i].objectID << " : " << strpkt[i].name << " : " << "PlayerData" << std::endl;
			}
		}
		_game.get()->component<PlayerPos>().set<PlayerPos>({ wm.value.row4.x, wm.value.row4.y }); //store player pos for later use in bullet
		box.value.min.x = -2.3f; box.value.min.y = -2.0f;
		box.value.max.x = 2.3f; box.value.max.y = 1.0f;
	})
	.add<Player>().add<Collidable>().add<GameObject>(); // Tag this entity as a Player

	return true;
}

bool BBG::PlayerData::Unload(std::shared_ptr<flecs::world> _game)
{
	// remove all players
	_game->defer_begin(); // required when removing while iterating!
		_game->each([](flecs::entity e, Player&) {
			e.destruct(); // destroy this entitiy (happens at frame end)
		});
	_game->defer_end(); // required when removing while iterating!

    return true;
}
