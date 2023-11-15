// define all ECS components related to identification
#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

// (avoid name collisions)
namespace BBG
{
	struct Paddle {}; //remember to delete

	struct Ball {};
	struct SubBall {};
	struct Gem {};
	struct Brick { };
	struct GameObject { };


	struct Player {};
	struct ProgressLvl { bool value; };
	struct Bullet {};
	struct Enemy {};
	struct Lives {};
	struct ControllerID { unsigned index = 0; };
	struct GemCache { flecs::entity g1; flecs::entity g2; };


	//level switching structs
	struct lvl1 { GW::MATH2D::GVECTOR2F value; };
	struct lvl2 { GW::MATH2D::GVECTOR2F value; };
	struct lvl3 { GW::MATH2D::GVECTOR2F value; };
	struct LevelUp { bool value; };

	struct WindXY { float x; float y; };
};

#endif