#include "PhysicsLogic.h"
#include "../Components/Physics.h"
#include "../Components/Gameplay.h"
#include "../Components/Identification.h"

bool BBG::PhysicsLogic::Init(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket>* gamepkt, GW::AUDIO::GAudio _audioEngine)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;

	// **** MOVEMENT ****
	// update velocity by acceleration
	game->system<Velocity, const Acceleration>("Acceleration System").each([](flecs::entity e, Velocity& v, const Acceleration& a)
		{
			GW::MATH2D::GVECTOR2F accel;
			GW::MATH2D::GVector2D::Scale2F(a.value, e.delta_time(), accel);
			GW::MATH2D::GVector2D::Add2F(accel, v.value, v.value);
		});

	// update position by velocity
	game->system<Position, const Velocity>("Translation System").each([](flecs::entity e, Position& p, const Velocity& v)
		{
			GW::MATH2D::GVECTOR2F speed;
			GW::MATH2D::GVector2D::Scale2F(v.value, e.delta_time(), speed);

			// adding is simple but doesn't account for orientation
			GW::MATH2D::GVector2D::Add2F(speed, p.value, p.value);
		});

	// **** CLEANUP ****
	// clean up any objects that end up offscreen
	game->system<const Position>("Cleanup System").each([](flecs::entity e, const Position& p)
		{
			if (p.value.x > 1.5f || p.value.x < -1.5f || p.value.y > 1.5f || p.value.y < -1.5f) { e.destruct(); }
		});

	// **** COLLISIONS ****
	// due to wanting to loop through all collidables at once, we do this in two steps:
	// 1. A System will gather all collidables into a shared std::vector
	// 2. A second system will run after, testing/resolving all collidables against each other

	//used for bricks
	//queryCache = game->query<Collidable, Position, Orientation>();
	queryCache = game->query<Collidable, WorldMatrix, BoxCollider>();
	//used for ball.
	ballCache = game->query<Collidable, WorldMatrix, BallColliders>();

	// only happens once per frame at the very start of the frame
	struct CollisionSystem {};


	// local definition so we control iteration count (singular)
	game->entity("Detect-Collisions").add<CollisionSystem>(); game->system<CollisionSystem>().each([this](CollisionSystem& s)
		{
			// This the base shape all objects use & draw, this might normally be a component collider.(ex:sphere/box)
			constexpr GW::MATH2D::GVECTOR2F poly[polysize] = //converting to components.
			{
				{ -0.5f, -0.5f }, { 0, 0.5f }, { 0.5f, -0.5f }, { 0, -0.25f }
			};


			ballCache.each([this](flecs::entity e, Collidable& c, WorldMatrix& w, BallColliders& b)
				{
					GW::MATH2D::GMATRIX3F matrix =
					{
						w.value.row1.x, w.value.row1.y, 0,
						w.value.row2.x, w.value.row2.y, 0, //orientation
						w.value.row4.x, w.value.row4.y, 1 //position
					};
					RECT rjsHouse;
					rjsHouse.owner = e;
					GW::MATH2D::GRECTANGLE2F rj;
					GW::MATH2D::GVECTOR3F tmi = { b.top.min.x, b.top.min.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, tmi, tmi);
					//std::cout << "TMI" << std::endl;
					//std::cout << tmi.x << " : " << tmi.y << std::endl;
					//std::cout << "WORLD" << std::endl;
					//std::cout << w.value.row4.x << " : " << w.value.row4.y << std::endl;
					//if(tmi.y >= 9.7f)
					//	std::cout << "TMI 10" << std::endl;
					GW::MATH2D::GVECTOR3F tma = { b.top.max.x, b.top.max.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, tma, tma);
					rj.min.x = tmi.x; rj.min.y = tmi.y; rj.max.x = tma.x; rj.max.y = tma.y;
					rjsHouse.rect = rj;
					ballColliders.push_back(rjsHouse);

					GW::MATH2D::GVECTOR3F bmi = { b.bottom.min.x, b.bottom.min.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, bmi, bmi);
					GW::MATH2D::GVECTOR3F bma = { b.bottom.max.x, b.bottom.max.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, bma, bma);
					rj.min.x = bmi.x; rj.min.y = bmi.y; rj.max.x = bma.x; rj.max.y = bma.y;
					rjsHouse.rect = rj;
					ballColliders.push_back(rjsHouse);

					GW::MATH2D::GVECTOR3F lmi = { b.left.min.x, b.left.min.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, lmi, lmi);
					GW::MATH2D::GVECTOR3F lma = { b.left.max.x, b.left.max.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, lma, lma);
					rj.min.x = lmi.x; rj.min.y = lmi.y; rj.max.x = lma.x; rj.max.y = lma.y;
					rjsHouse.rect = rj;
					ballColliders.push_back(rjsHouse);

					GW::MATH2D::GVECTOR3F rmi = { b.right.min.x, b.right.min.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, rmi, rmi);
					GW::MATH2D::GVECTOR3F rma = { b.right.max.x, b.right.max.y, 1 };
					GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, rma, rma);
					rj.min.x = rmi.x; rj.min.y = rmi.y; rj.max.x = rma.x; rj.max.y = rma.y;
					rjsHouse.rect = rj;
					ballColliders.push_back(rjsHouse);
				});
			// collect any and all collidable objects
			queryCache.each([this, poly](flecs::entity e, Collidable& c, WorldMatrix& w, BoxCollider& b)
				{
					// create a 3x3 matrix for transformation
					GW::MATH2D::GMATRIX3F matrix =
					{
						w.value.row1.x, w.value.row1.y, 0,
						w.value.row2.x, w.value.row2.y, 0,
						w.value.row4.x, w.value.row4.y, 1
					};
					RECT polygon; // compute buffer for this objects polygon
					// This is critical, if you want to store an entity handle it must be mutable
					polygon.owner = e; // allows later changes

						GW::MATH2D::GRECTANGLE2F rct;
						GW::MATH2D::GVECTOR3F v1 = { b.value.min.x, b.value.min.y, 1 };
						GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, v1, v1);
						GW::MATH2D::GVECTOR3F v2 = { b.value.max.x, b.value.max.y, 1 };
						GW::MATH2D::GMatrix2D::MatrixXVector3F(matrix, v2, v2);
						rct.min.x = v1.x; rct.min.y = v1.y; rct.max.x = v2.x; rct.max.y = v2.y;
						polygon.rect = rct;
					


					// add to vector
					brickColliders.push_back(polygon);
					//vector for the ball colliders.
				});
			// loop through the testCahe resolving all collisions
			for (int i = 0; i < brickColliders.size(); ++i)
			{

				// the inner loop starts at the entity after you so you don't double check collisions
				//change to fit the ball collider count
				for (int j = 0; j < ballColliders.size(); ++j)
				{

					// test the two world space polygons for collision
					// possibly make this cheaper by leaving one of them local and using an inverse matrix
					GW::MATH2D::GCollision2D::GCollisionCheck2D result;
					//change to test rect to rect
					//GW::MATH2D::GCollision2D::TestPolygonToPolygon2F(testCache[i].poly, polysize, testCache[j].poly, polysize, result);
					GW::MATH2D::GCollision2D::TestRectangleToRectangle2F(ballColliders[j].rect, brickColliders[i].rect, result);
					
					//check if results is true and ball is active
					if (result == GW::MATH2D::GCollision2D::GCollisionCheck2D::COLLISION && !brickColliders[i].owner.has<Gem>()) //keeps ball from hitting gem
					{
						// Create an ECS relationship between the colliders
						// Each system can decide how to respond to this info independently
						//set bool check to true.	

						ballColliders[j].owner.get_ref<BallColliders>().get()->colliderChecks[j] = true;
						//std::cout << "I HIT SOMETHING" << std::endl;
						//if (!ballColliders[j].owner.owns<CollidedWith>())
							ballColliders[j].owner.add<CollidedWith>(brickColliders[i].owner);

						brickColliders[i].owner.add<CollidedWith>(ballColliders[j].owner);
					}
				}
			}
			// wipe the test cache for the next frame (keeps capacity intact)

			if (game.get()->get_ref<GemCache>().get()->g1.get_ref<ActiveGem>().get() != nullptr && game.get()->get_ref<GemCache>().get()->g1.get_ref<ActiveGem>().get()->value)
			{
				RECT gem; // stores gem
				RECT paddle;
				for (int i = 0; i < brickColliders.size(); i++)
				{

					if (brickColliders[i].owner.get_ref<ObjectID>().get()->value ==
						game.get()->get_ref<GemCache>().get()->g1.get_ref<ObjectID>().get()->value)
						gem = brickColliders[i]; //save gem for later collision check
					else if (brickColliders[i].owner.has<Player>())
					{
						paddle = brickColliders[i];
					}
				}


					GW::MATH2D::GCollision2D::GCollisionCheck2D result;
					GW::MATH2D::GCollision2D::TestRectangleToRectangle2F(gem.rect, paddle.rect, result);

					//check if results is true and ball is active
					if (result == GW::MATH2D::GCollision2D::GCollisionCheck2D::COLLISION)
					{
						ballColliders[0].owner.add<CollidedWith>(gem.owner);
					}
				

			}

			brickColliders.clear();
			ballColliders.clear();
		});
	return true;
}

bool BBG::PhysicsLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Acceleration System").enable();
		game->entity("Translation System").enable();
		game->entity("Cleanup System").enable();
	}
	else {
		game->entity("Acceleration System").disable();
		game->entity("Translation System").disable();
		game->entity("Cleanup System").disable();
	}
	return true;
}

bool BBG::PhysicsLogic::Shutdown()
{
	queryCache.destruct(); // fixes crash on shutdown
	game->entity("Acceleration System").destruct();
	game->entity("Translation System").destruct();
	game->entity("Cleanup System").destruct();
	return true;
}
