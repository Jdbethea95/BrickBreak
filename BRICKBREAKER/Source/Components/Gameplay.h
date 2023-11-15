// define all ECS components related to gameplay
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

// (avoid name collisions)
namespace BBG
{
	struct Life { int value; };

	struct Damage { int value; };
	struct Health { int value; };
	struct Firerate { float value; };
	struct Cooldown { float value; };
	struct LevelPOS { GW::MATH2D::GVECTOR2F pos; };


	struct ActiveBall { bool value;  };
	struct ActiveGem { bool value; };
	struct EnemyCount { int value; };

	struct BallArray { std::vector<flecs::entity> sBalls;};
	struct SballID { int id; };
	struct ActiveSBALLS { int activeCount; };

	struct SOUNDS 
	{
		GW::AUDIO::GSound hit;
		GW::AUDIO::GSound win;
		GW::AUDIO::GSound lose;
	};

	struct Sound { GW::AUDIO::GSound value; };
	// gameplay tags (states)
	struct Firing {};
	struct Charging {};

	struct ReadyUp { bool plyer; bool ball; bool game; };
	// powerups
	struct ChargedShot { int max_destroy; };
};

#endif