#include "PlayerLogic.h"
#include "../Components/Identification.h"
#include "../Components/Physics.h"
#include "../Components/Visuals.h"
#include "../Components/Gameplay.h"
#include "../Entities/Prefabs.h"
#include "../Events/Playevents.h"
#include "../Packet.h"

using namespace BBG;
using namespace GW::INPUT; // input libs
using namespace GW::AUDIO; // audio libs

// Connects logic to traverse any players and allow a controller to manipulate them
bool BBG::PlayerLogic::Init(std::shared_ptr<flecs::world> _game,
	std::weak_ptr<const GameConfig> _gameConfig,
	GW::INPUT::GInput _immediateInput,
	GW::INPUT::GBufferedInput _bufferedInput,
	GW::INPUT::GController _controllerInput,
	GW::AUDIO::GAudio _audioEngine,
	GW::CORE::GEventGenerator _eventPusher, std::vector<GamePacket>* gamePkt, int& currLvl)
{
	// save a handle to the ECS & game settings
	game = _game;
	gameConfig = _gameConfig;
	immediateInput = _immediateInput;
	bufferedInput = _bufferedInput;
	controllerInput = _controllerInput;
	audioEngine = _audioEngine;
	game.get()->component<WindXY>().set<WindXY>({ 14.0f, 5.0f });
	left = game.get()->get_ref<WindXY>().get()->x;
	right = game.get()->get_ref<WindXY>().get()->y;
	// Init any helper systems required for this task
	std::shared_ptr<const GameConfig> readCfg = gameConfig.lock();
	int width = (*readCfg).at("Window").at("width").as<int>();
	float speed = (*readCfg).at("Player1").at("speed").as<float>();
	chargeTime = (*readCfg).at("Player1").at("chargeTime").as<float>();
	// add logic for updating players
	playerSystem = game->system<Player, Position, ControllerID, WorldMatrix, ObjectID, ProgressLvl, Health>("Player System")
		.iter([this, currLvl, speed, gamePkt](flecs::iter it, Player*, Position* p, ControllerID* c, WorldMatrix* wm, ObjectID* id, ProgressLvl* prg, Health* h) {
		for (auto i : it) {
			// left-right movement
			float xaxis = 0, input = 0;
			// Use the controller/keyboard to move the player around the screen			
			if (c[i].index == 0) { // enable keyboard controls for player 1
				immediateInput.GetState(G_KEY_LEFT, input);
				xaxis -= input; //denb
				immediateInput.GetState(G_KEY_RIGHT, input);
				xaxis += input;
			}
			// grab left-thumb stick
			controllerInput.GetState(c[i].index, G_LX_AXIS, input); xaxis += input;
			controllerInput.GetState(c[i].index, G_DPAD_LEFT_BTN, input); xaxis -= input;
			controllerInput.GetState(c[i].index, G_DPAD_RIGHT_BTN, input); xaxis += input;
			xaxis = G_LARGER(xaxis, -1);// cap right motion
			xaxis = G_SMALLER(xaxis, 1);// cap left motion
			// apply movement
			//Converting to new input;
			//std::cout << xaxis << std::endl; //here to see if it will print to console, atm it wont
			wm->value.row4.x += xaxis * it.delta_time() * speed;
			// limit the player to stay within -1 to +1 NDC
			wm->value.row4.x = G_LARGER(wm->value.row4.x, -left);
			wm->value.row4.x = G_SMALLER(wm->value.row4.x, +right);
			float bubbles;
			immediateInput.GetState(G_KEY_ENTER, bubbles);

			prg->value = game.get()->get_ref<LevelUp>().get()->value;
			if (prg->value)
			{

				//std::cout << h->value << ": COUNTER\n";
				game.get()->get_ref<LevelUp>().get()->value = false;
				h->value++;
				wm->value.row4.x = game.get()->get_ref<lvl2>().get()->value.x;
				game.get()->get_ref<WindXY>().get()->x = -11.5;
				game.get()->get_ref<WindXY>().get()->y = 30;
				left = game.get()->get_ref<WindXY>().get()->x;
				right = game.get()->get_ref<WindXY>().get()->y;
				game.get()->get_ref<ReadyUp>().get()->plyer = true;
				if (currLvl <= 0)
				{
					std::cout << "LEVEL 3\n";
					wm->value.row4.x = game.get()->get_ref<lvl3>().get()->value.x;
					game.get()->get_ref<WindXY>().get()->x = -11.5;
					game.get()->get_ref<WindXY>().get()->y = 60;
					left = game.get()->get_ref<WindXY>().get()->x;
					right = game.get()->get_ref<WindXY>().get()->y;
					game.get()->get_ref<ReadyUp>().get()->plyer = true;
				}


			}


			game.get()->component<PlayerPos>().set<PlayerPos>({ wm->value.row4.x, wm->value.row4.y }); //update player pos 
			//will add a check here to check the row for vs the old row4 to detect changes to push.
			gamePkt->push_back(GamePacket(wm->value, id->value, "Player"));

			//// fire weapon if they are in a firing state
			//if (it.entity(i).has<Firing>()) {
			//	Position offset = p[i];
			//	offset.value.y += 0.05f;
			//	FireLasers(it.world(), offset);
			//	it.entity(i).remove<Firing>();
			//}
		}
		// process any cached button events after the loop (happens multiple times per frame)
		ProcessInputEvents(it.world());
			});

	// Create an event cache for when the spacebar/'A' button is pressed
	pressEvents.Create(Max_Frame_Events); // even 32 is probably overkill for one frame

	// register for keyboard and controller events
	bufferedInput.Register(pressEvents);
	controllerInput.Register(pressEvents);

	// create the on explode handler
	onExplode.Create([this](const GW::GEvent& e) {
		BBG::PLAY_EVENT event; BBG::PLAY_EVENT_DATA eventData;
		if (+e.Read(event, eventData)) {
			// only in here if event matches
			std::cout << "Enemy Was Destroyed!\n";


		}
		});
	_eventPusher.Register(onExplode);

	return true;
}

// Free any resources used to run this system
bool BBG::PlayerLogic::Shutdown()
{
	playerSystem.destruct();
	game.reset();
	gameConfig.reset();

	return true;
}

// Toggle if a system's Logic is actively running
bool BBG::PlayerLogic::Activate(bool runSystem)
{
	if (playerSystem.is_alive()) {
		(runSystem) ?
			playerSystem.enable()
			: playerSystem.disable();
		return true;
	}

	return false;
}

bool BBG::PlayerLogic::ProcessInputEvents(flecs::world& stage)
{
	// pull any waiting events from the event cache and process them
	GW::GEvent event;
	while (+pressEvents.Pop(event)) {
		bool fire = false;
		GController::Events controller;
		GController::EVENT_DATA c_data;
		GBufferedInput::Events keyboard;
		GBufferedInput::EVENT_DATA k_data;
		// these will only happen when needed
		if (+event.Read(keyboard, k_data)) {
			if (keyboard == GBufferedInput::Events::KEYPRESSED) {
				if (k_data.data == G_KEY_SPACE) {
					fire = true;
					chargeStart = stage.time();
				}
			}
			/*if (keyboard == GBufferedInput::Events::KEYRELEASED) {
				if (k_data.data == G_KEY_SPACE) {
					chargeEnd = stage.time();
					if (chargeEnd - chargeStart >= chargeTime) {
						fire = true;
					}
				}
			}*/
		}
		else if (+event.Read(controller, c_data)) {
			if (controller == GController::Events::CONTROLLERBUTTONVALUECHANGED) {
				if (c_data.inputValue > 0 && c_data.inputCode == G_SOUTH_BTN)
					fire = true;
			}
		}
		if (fire) {
			// grab player one and set them to a firing state
			stage.entity("Player One").add<Firing>();
		}
	}
	return true;
}

// play sound and launch two laser rounds
bool BBG::PlayerLogic::FireLasers(flecs::world& stage, Position origin)
{
	// Grab the prefab for a laser round
	flecs::entity bullet;
	RetreivePrefab("Lazer Bullet", bullet);

	origin.value.x -= 0.05f;
	auto laserLeft = stage.entity().is_a(bullet)
		.set<Position>(origin);
	origin.value.x += 0.1f;
	auto laserRight = stage.entity().is_a(bullet)
		.set<Position>(origin);
	// if this shot is charged
	if (chargeEnd - chargeStart >= chargeTime) {
		chargeEnd = chargeStart;
		laserLeft.set<ChargedShot>({ 2 })
			.set<Material>({ 1,0,0 });
		laserRight.set<ChargedShot>({ 2 })
			.set<Material>({ 1,0,0 });
	}

	// play the sound of the Lazer prefab
	GW::AUDIO::GSound shoot = *bullet.get<GW::AUDIO::GSound>();
	shoot.Play();

	return true;
}