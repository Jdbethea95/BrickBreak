#include <random>
#include "BulletLogic.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "../Components/Gameplay.h"
#include "../Packet.h"

using namespace BBG; 

//// Connects logic to traverse any players and allow a controller to manipulate them

bool BBG::BallLogic::Init(std::shared_ptr<flecs::world> _game, std::weak_ptr<const GameConfig> _gameConfig, std::vector<GamePacket>* gamepkt,
	GW::INPUT::GInput _immediateInput,
	GW::INPUT::GBufferedInput _bufferedInput,
	GW::INPUT::GController _controllerInput, bool& reset, std::vector<bool>* levels, int& lvlindex, int& hs, int& life)
{
	std::shared_ptr<const GameConfig> readCfg = _gameConfig.lock();

	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	immediateInput = _immediateInput;
	float height = (*readCfg).at("Window").at("height").as<float>();
	float width = (*readCfg).at("Window").at("width").as<float>();
	int nextLevel = currentLvl;
	// destroy any bullets that have the CollidedWith relationship
	gmpt = gamepkt;
	lvls = levels;
	ballSystem = game->system<Ball, WorldMatrix*, ObjectID*, ActiveBall*, BallColliders*, Velocity*>("Ball System").each([&](flecs::entity e, Ball, WorldMatrix* wm, ObjectID* id, ActiveBall* bl, BallColliders* bc, Velocity* vel)
		{

			float input, god, ungod;
			immediateInput.GetState(G_KEY_SPACE, input);
			immediateInput.GetState(G_KEY_G, god);
			immediateInput.GetState(G_KEY_H, ungod);
			if (god != 0)
				game.get()->get_ref<Life>().get()->value += 999999;
			else if (ungod != 0)
				game.get()->get_ref<Life>().get()->value = 3;

			life = game.get()->get_ref<Life>().get()->value;

			//debug keys
			float debug1, debug2, debug3;
			immediateInput.GetState(G_KEY_NUMPAD_1, debug1); immediateInput.GetState(G_KEY_NUMPAD_2, debug2); immediateInput.GetState(G_KEY_M, debug3);
			int count = alienCount;

			//locl variable to change gem speed and pos;
			bool presentGem = gemPresent;
			bool sballTime = timeForSball;
			GW::MATH2D::GVECTOR3F gemPos;
			std::vector<int> deadAliens;
			if (!reset)
			{

				//check for ball launch
				if (input != 0 && bl != nullptr)
				{
					vel->value.y = vel->speed;
					bl->value = true;
				}


				//is ball active? Has it been launched?
				if (bl != nullptr && bl->value && wm->value.row4.y <= 21 && !down)
				{

					if (vel->value.y <= 0)
						vel->value.y = vel->speed;
					down = true;
				}




#pragma region WindowCollision
				//Window Collision
				if (wm->value.row4.x >= game.get()->get_ref<WindXY>().get()->y && vel->value.x >= 0)
				{
					vel->value.x = 0;
					vel->value.x = -vel->speed;
				}
				else if (wm->value.row4.x <= -game.get()->get_ref<WindXY>().get()->x && vel->value.x != 0) {
					vel->value.x = 0;
					vel->value.x = vel->speed;

				}
				else if (wm->value.row4.y > 20 && vel->value.y >= 0) {
					vel->value.y = 0;
					vel->value.y = -vel->speed;
				}
				else if (game.get()->get_ref<Life>().get()->value > 999 && wm->value.row4.y < -13)
				{
					vel->value.y = 0;
					vel->value.y = vel->speed;
				}

#pragma endregion

				GamePacket brick = GamePacket(GW::MATH::GMATRIXF(), -1, "NULL");
				std::vector<GamePacket> blocks;
				e.each<CollidedWith>([&e, bc, &id, &vel, &hs, &brick, &blocks, &count, &bl, &deadAliens, &presentGem, &gemPos, &sballTime](flecs::entity hit)
					{
						//hit has the position we will need for reflecting later.
							//if player follow paddle
								//add bool to force a tracker
											//check if brick.

						//Ball Collision Interactions.
						if ((hit.has<Brick>() || hit.has<Enemy>())) //player and bricks are entering.
						{
							//sound happens here
							if (!e.has<SballID>())
								e.get_ref<SOUNDS>().get()->hit.Play();

							//Left //Right calling L and R below T and B causes different ball behavior.
							if (bc->colliderChecks[2] && vel->value.x <= 0)
							{
								vel->value.x = 0;
								vel->value.x += vel->speed;
								std::cout << "Left" << std::endl;
								bc->colliderChecks[2] = false;
								bc->colliderChecks[3] = false;
							}
							else if (bc->colliderChecks[3] && vel->value.x >= 0)
							{
								vel->value.x = 0;
								vel->value.x -= vel->speed;
								std::cout << "Right" << std::endl;
								bc->colliderChecks[3] = false;
							}
							//Top //Bottom
							if (bc->colliderChecks[0] && vel->value.y >= 0)
							{
								vel->value.y = 0;
								vel->value.y = vel->value.y - vel->speed;
								std::cout << "Top" << std::endl;
								bc->colliderChecks[0] = false;
								bc->colliderChecks[1] = false;
							}
							if (bc->colliderChecks[1] && vel->value.y <= 0)
							{
								vel->value.y = 0;
								vel->value.y = vel->value.y + vel->speed;
								std::cout << "Bottom" << std::endl;
								bc->colliderChecks[1] = false;
							}


							if (hit.has<Enemy>())
							{
								hs += (rand() % 201) + 1;
								bool doit = true;
								for (size_t i = 0; i < deadAliens.size(); i++)
								{
									if (id->value == deadAliens[i])
									{
										doit = false;
									}
								}
								if (doit)
								{
									count--;
									deadAliens.push_back(id->value);
								}

							}
							else if (hit.has<Brick>())
							{
								int test = rand() % 101;
								hs += (rand() % 101) + 1;

								if (test > 49 && !presentGem && !e.has<SballID>())
								{
									presentGem = true;
									gemPos.x = hit.get_ref<WorldMatrix>().get()->value.row4.x;
									gemPos.y = hit.get_ref<WorldMatrix>().get()->value.row4.y;
									gemPos.z = hit.get_ref<WorldMatrix>().get()->value.row4.z;

									std::cout << "GEM!" << std::endl;
									std::cout << "(" << gemPos.x << " , " << gemPos.y << ")" << std::endl;
									std::cout << "BOX!" << std::endl;
									std::cout << "(" << hit.get_ref<WorldMatrix>().get()->value.row4.x
										<< " , " << hit.get_ref<WorldMatrix>().get()->value.row4.y << ")" << std::endl;
								}

							}


							hit.get_ref<WorldMatrix>().get()->value.row4.x = 100;
							hit.get_ref<WorldMatrix>().get()->value.row4.y = 100;
							int target = hit.get_ref<ObjectID>().get()->value;
							brick.matrix = hit.get_ref<WorldMatrix>().get()->value;
							brick.objectID = target;
							brick.name = "Changed";
							blocks.push_back(brick);

						}
						else if (hit.has<Player>()) //players and bricks are entering
						{
							//std::cout << "Player is here";
								//Top //Bottom
							if (bc->colliderChecks[0] && vel->value.y >= 0)
							{
								vel->value.y = 0;
								vel->value.y = vel->value.y + vel->speed;
								std::cout << "Toop" << std::endl;
								bc->colliderChecks[0] = false;

								if (bc->colliderChecks[2])
									vel->value.x = vel->value.x + vel->speed;
								if (bc->colliderChecks[3])
									vel->value.x = vel->value.x - vel->speed;
							}
							if (bc->colliderChecks[1] && vel->value.y <= 0)
							{
								vel->value.y = 0;
								vel->value.y = vel->value.y + vel->speed;
								std::cout << "Boottom" << std::endl;
								bc->colliderChecks[1] = false;

								if (bc->colliderChecks[2])
									vel->value.x = vel->value.x + vel->speed;
								if (bc->colliderChecks[3])
									vel->value.x = vel->value.x - vel->speed;
							}
						}
						else if (hit.has<Gem>() && !e.has<SballID>())
						{
							hs += (rand() % 51) + 1;
							hit.get_ref<GW::AUDIO::GSound>().get()->Play();
							presentGem = false;
							hit.get_ref<WorldMatrix>().get()->value.row4.x = 100;
							hit.get_ref<WorldMatrix>().get()->value.row4.y = 100;
							hit.get_ref<ActiveGem>().get()->value = false;
							blocks.push_back(GamePacket(hit.get_ref<WorldMatrix>().get()->value, hit.get_ref<ObjectID>().get()->value));
							sballTime = true;
						}


						e.remove<CollidedWith>(hit);

					});

				// if you have collidedWith realtionship then be destroyed
				if (e.has<CollidedWith>(flecs::Wildcard))
				{
					//remove collided with tag once we do this.
					e.remove<CollidedWith>();
				}

				alienCount = count;
				timeForSball = sballTime; //this saves the results so they are not lost
				gemPresent = presentGem; //the lambda can't take vars from the .h. Not clear why, still researching.
				//gem spawn and fall
				if (presentGem)
				{
					if (!game.get()->get_ref<GemCache>().get()->g1.get_ref<ActiveGem>().get()->value)
					{
						game.get()->get_ref<GemCache>().get()->g1.get_ref<WorldMatrix>().get()->value.row4.x = gemPos.x;
						game.get()->get_ref<GemCache>().get()->g1.get_ref<WorldMatrix>().get()->value.row4.y = gemPos.y;
						game.get()->get_ref<GemCache>().get()->g1.get_ref<WorldMatrix>().get()->value.row4.z = gemPos.z; //the gem starts behind the camera
						game.get()->get_ref<GemCache>().get()->g1.get_ref<ActiveGem>().get()->value = true;
					}
					else
					{
						game.get()->get_ref<GemCache>().get()->g1.get_ref<WorldMatrix>().get()->value.row4.y -= 0.01f;
					}
					gmpt->push_back(GamePacket(game.get()->get_ref<GemCache>().get()->g1.get_ref<WorldMatrix>().get()->value,
						game.get()->get_ref<GemCache>().get()->g1.get_ref<ObjectID>().get()->value));
				}


				//spawn balls if sball perk was selected
				if (sballTime && game.get()->get_ref<ActiveSBALLS>().get()->activeCount <= 0)
				{
					for (size_t i = 0; i < 3; i++)
					{
						GW::MATH2D::GVECTOR2F vec;
						vec.x = e.get_ref<WorldMatrix>().get()->value.row4.x;
						vec.y = e.get_ref<WorldMatrix>().get()->value.row4.y;
						gmpt->push_back(ActivateBalls(game, e.get_ref<WorldMatrix>().get()->value.row4.z, i, true, vec));
					}
					timeForSball = false;
				}

				//win and lose conditions
				if (count <= 0)
				{

					if (e.has<SballID>())
					{
						gmpt->push_back(ActivateBalls(game, -20, e.get_ref<SballID>().get()->id, false));
						game.get()->get_ref<ActiveSBALLS>().get()->activeCount -= 1;
					}
					else
					{
						
						std::cout << "WINNER WINNER" << std::endl;
						game.get()->get_ref<EnemyCount>().get()->value = count;
						game.get()->get_ref<LevelUp>().get()->value = true;
						count = alienCount;
						bl->value = false;
						lvls->at(lvlindex) = true;
						game.get()->get_ref<ReadyUp>().get()->ball = true;
					}

					if (game.get()->get_ref<ReadyUp>().get()->plyer && game.get()->get_ref<ReadyUp>().get()->game &&
						game.get()->get_ref<ReadyUp>().get()->ball)
					{
						vel->value.x = 0;
						alienCount = 3;
						game.get()->get_ref<ReadyUp>().get()->game = false;
						game.get()->get_ref<ReadyUp>().get()->ball = false;
						game.get()->get_ref<ReadyUp>().get()->plyer = false;
					}

				}
				if (wm->value.row4.y <= -15.0f) //if falls below paddle reset ball location
				{
					if (game.get()->get_ref<ActiveSBALLS>().get()->activeCount <= 0 && !e.has<SballID>())
					{
						
						
						vel->value.x = 0; vel->value.y = 0;
						bl->value = false;
						down = false;
						game.get()->get_ref<ActiveSBALLS>().get()->activeCount = 0;
						game.get()->get_ref<Life>().get()->value -= 1;
						std::cout << "Lost a life : " << game.get()->get_ref<Life>().get()->value << " Remaining\n";
					}
					else
					{
						vel->value.x = 0; vel->value.y = 0;
						if (e.has<SballID>())
						{
							gmpt->push_back(ActivateBalls(game, -20, e.get_ref<SballID>().get()->id, false));
							game.get()->get_ref<ActiveSBALLS>().get()->activeCount -= 1;
						}
						else { gmpt->push_back(GamePacket(wm->value, id->value)); }
					}

				}


				//follow paddle if not active
				if (input == 0 && !bl->value)
				{
					wm->value.row4.x = game.get()->get_ref<PlayerPos>().get()->value.x - 1.5f;
					wm->value.row4.y = game.get()->get_ref<PlayerPos>().get()->value.y + 0.5f;
					gmpt->push_back(GamePacket(wm->value, id->value));
					if (game.get()->get_ref<Life>().get()->value <= 0)
					{
						reset = true;
						e.get_ref<SOUNDS>().get()->lose.Play();
						game.get()->get_ref<Life>().get()->value = 3;
					}
				}



				//DEBUG CHECKS
				if (debug1 != 0 || d1)
				{
					if (d1 && debug1 != 0)
						d1 = !d1;

					std::cout << " Velocity " << std::endl;
					std::cout << vel->value.x << " : " << vel->value.y << std::endl;
				}
				if (debug2 != 0 || d2)
				{
					if (d2 && debug1 != 0)
						d2 = !d2;

					std::cout << " Ball POS " << std::endl;
					std::cout << wm->value.row4.x << " : " << wm->value.row4.y << std::endl;
				}
				if (debug3 != 0)
				{
					count--; std::cout << count << ": Count\n";
				}


				if (vel->value.y != 0 || vel->value.x != 0)
				{
					wm->value.row4.x += vel->value.x; wm->value.row4.y += vel->value.y;
					gmpt->push_back(GamePacket(wm->value, id->value));
				}

				for (int i = 0; i < blocks.size(); i++)
				{
					if (blocks[i].name != "NULL")
						gmpt->push_back(blocks[i]);
				}

			}
			else
			{
				std::cout << "Continue?\n";
				if (debug3 != 0)
					reset = false;
			}
		});

	return true;
}

bool BBG::BallLogic::Activate(bool runSystem)
{
	if (runSystem) {
		game->entity("Ball System").enable();
	}
	else {
		game->entity("Ball System").disable();
	}
	return false;
}
GamePacket BBG::BallLogic::ActivateBalls(std::shared_ptr<flecs::world> game, int zSize, int index, bool toggle, GW::MATH2D::GVECTOR2F vec)
{
	if (vec.x + vec.y == 0) //the gw vector doesn't have contructors so we made this here.
	{
		vec.x = 150; vec.y = 150;
	}

	if (toggle)
	{
		float x;
		if ((rand() % 2) == 1)
			x = (rand() % 11) * -0.01f;
		else
			x = (rand() % 11) * 0.01f;

		if (index < game.get()->get_ref<BallArray>().get()->sBalls.size())
		{
			game.get()->get_ref<BallArray>().get()->sBalls[index].add<Ball>().add<Collidable>();
			game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value.row4.z = zSize;
			game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value.row4.x = vec.x;
			game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value.row4.y = vec.y;
			game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<ActiveBall>().get()->value = true;
			game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<Velocity>().get()->value = { x,0.1f };
			game.get()->get_ref<ActiveSBALLS>().get()->activeCount += 1;
		}
	}
	else if (game.get()->get_ref<ActiveSBALLS>().get()->activeCount != 0)
	{
		game.get()->get_ref<BallArray>().get()->sBalls[index].remove<Ball>().remove<Collidable>();
		game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value.row4.z = zSize;
		game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value.row4.x = vec.x;
		game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value.row4.y = vec.y;
		game.get()->get_ref<ActiveSBALLS>().get()->activeCount -= 1;
	}
	return GamePacket(game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<WorldMatrix>().get()->value,
		game.get()->get_ref<BallArray>().get()->sBalls[index].get_ref<ObjectID>().get()->value);
}
bool BBG::BallLogic::Shutdown()
{
	game->entity("Ball System").destruct();
	// invalidate the shared pointers
	game.reset();
	gameConfig.reset();
	return true;
}
