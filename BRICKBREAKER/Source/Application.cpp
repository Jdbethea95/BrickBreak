#include "Application.h"
// open some Gateware namespaces for conveinence 
// NEVER do this in a header file!
using namespace GW;
using namespace CORE;
using namespace SYSTEM;
using namespace GRAPHICS;
using namespace BBG;



bool Application::Init()
{
	eventPusher.Create();

	// load all game settigns
	gameConfig = std::make_shared<GameConfig>();
	// create the ECS system
	game = std::make_shared<flecs::world>();

	// init all other systems
	if (InitWindow() == false)
		return false;
	if (InitLevelData() == false)
		return false;
	if (InitInput() == false)
		return false;
	if (InitAudio() == false)
		return false;
	if (InitGraphics() == false)
		return false;

	//Here if statment to iniEntity
	if (InitEntities(collectionPack.startPacket) == false)
		return false;
	//Here if statment to iniSystem
	if (InitSystems(&collectionPack.gamePacket, collectionPack.startPacket, reset) == false)
		return false;

	return true;
}

bool Application::Run()
{
	//shared pointer of the dataloader level_data that will be shared with a weak pointer inside the renderer. 
		//this will be availabe to flecs can alter the information as needed and the renderer can reload the alterered information.
	game.get()->component<ReadyUp>().set<ReadyUp>({ false, false, false });
	bool once = true;
	VkClearValue clrAndDepth[2];
	clrAndDepth[0].color = { {0, 0, 0, 1} };
	clrAndDepth[1].depthStencil = { 1.0f, 0u };
	// grab vsync selection
	bool vsync = gameConfig->at("Window").at("vsync").as<bool>();
	// set background color from settings
	const char* channels[] = { "red", "green", "blue" };
	for (int i = 0; i < std::size(channels); ++i) {
		clrAndDepth[0].color.float32[i] =
			gameConfig->at("BackGroundColor").at(channels[i]).as<float>();
	}
	// create an event handler to see if the window was closed early
	bool winClosed = false;
	GW::CORE::GEventResponder winHandler;
	winHandler.Create([&winClosed](GW::GEvent e) {
		GW::SYSTEM::GWindow::Events ev;
		if (+e.Read(ev) && ev == GW::SYSTEM::GWindow::Events::DESTROY)
			winClosed = true;
		});

	//D3D11 stuff added here
	float clr[] = { 0.5f, 0.5f, 0.0f, 1 };
	bool whyHaveYouDoneThisToMe = false;
	winHandler.Create([&](const GW::GEvent& e) {
		GW::SYSTEM::GWindow::Events q;
		if (+e.Read(q) && q == GWindow::Events::RESIZE)
			whyHaveYouDoneThisToMe = true;
		});

	window.Register(winHandler);
	Renderer renderer(window, d3d11, lvlData, immediateInput, gamePads);
	int dumb = 0; bool start = false; bool pause = false;
	while (+window.ProcessWindowEvents())
	{
		if (currentScore > highScore)
			highScore = currentScore;
		IDXGISwapChain* swap;
		ID3D11DeviceContext* con;
		ID3D11RenderTargetView* view;
		ID3D11DepthStencilView* depth;
		if (+d3d11.GetImmediateContext((void**)&con) &&
			+d3d11.GetRenderTargetView((void**)&view) &&
			+d3d11.GetDepthStencilView((void**)&depth) &&
			+d3d11.GetSwapchain((void**)&swap))
		{
			con->ClearRenderTargetView(view, clr);
			con->ClearDepthStencilView(depth, D3D11_CLEAR_DEPTH, 1, 0);

			float ButterCup, Blossom, mojojojo;

			immediateInput.GetState(G_KEY_P, ButterCup);
			immediateInput.GetState(G_KEY_O, Blossom);
			immediateInput.GetState(G_KEY_T, mojojojo);

			if (!start)
			{
				PauseSystems(false);
			}
			 if (mojojojo != 0)
			{
				PauseSystems(true);
				start = true;
			}

			if (start)
			{
				if (ButterCup != 0)
				{
					PauseSystems(false);
					pause = true;
				}
				else if (Blossom != 0)
				{
					PauseSystems(true);
					pause = false;
				}
			}
			
			game.get()->progress();
			if (levels[levelindex])
			{
				float bubbles;
				int temp = 2;
				immediateInput.GetState(G_KEY_ENTER, bubbles);
				if (bubbles != 0 && game.get()->get_ref<ReadyUp>().get()->game == false)
				{
					if (levels[levelindex])
						currentLevel--;
					levelindex++;
					std::cout << "currentlevel: " << currentLevel << "\n";
					game.get()->get_ref<ReadyUp>().get()->game = true;
					ballSystem.Activate(true);

				}

			}
			//GameLoop();
			renderer.UpdateCamera();
			renderer.ONRESIZE(window, whyHaveYouDoneThisToMe);
			renderer.GameUpdate(collectionPack.gamePacket, currentLevel);
			collectionPack.gamePacket.clear();
			renderer.Render();
			renderer.UpdateText(highScore, currentScore, lifeScore, pause, start);
			swap->Present(1, 0);
			// release incremented COM reference counts
			swap->Release();
			view->Release();
			depth->Release();
			con->Release();
		}
		else
			return false;
	}
	return true;
}

bool Application::Shutdown()
{
	ini::IniFile myini;
	myini["SaveData"]["highscore"] = highScore;
	myini.save("../FontData/SaveData.ini");
	//disconnect systems from global ECS
	if (playerSystem.Shutdown() == false)
		return false;
	if (levelSystem.Shutdown() == false)
		return false;
	if (resetSystem.Shutdown() == false)
		return false;
	//if (vkRenderingSystem.Shutdown() == false)
	//	return false;
	if (physicsSystem.Shutdown() == false)
		return false;
	if (ballSystem.Shutdown() == false)
		return false;

	if (enemySystem.Shutdown() == false)
		return false;

	return true;
}

bool Application::InitWindow()
{
	// grab settings
	int width = gameConfig->at("Window").at("width").as<int>();
	int height = gameConfig->at("Window").at("height").as<int>();
	int xstart = gameConfig->at("Window").at("xstart").as<int>();
	int ystart = gameConfig->at("Window").at("ystart").as<int>();
	std::string title = gameConfig->at("Window").at("title").as<std::string>();
	// open window
	if (+window.Create(xstart, ystart, width, height, GWindowStyle::WINDOWEDLOCKED) &&
		+window.SetWindowName(title.c_str())) {
		return true;
	}
	return false;
}

bool Application::InitInput()
{
	if (-gamePads.Create())
		return false;
	if (-immediateInput.Create(window))
		return false;
	if (-bufferedInput.Create(window))
		return false;
	return true;
}

bool Application::InitAudio()
{
	if (-audioEngine.Create())
		return false;
	return true;
}

bool Application::InitGraphics()
{
#ifndef NDEBUG
	if (+d3d11.Create(window, GW::GRAPHICS::DEPTH_BUFFER_SUPPORT))
		return true;
#else
	if (+d3d11.Create(window, GW::GRAPHICS::DEPTH_BUFFER_SUPPORT))
		return true;
#endif
	return false;
}

bool Application::InitEntities(std::vector<GamePacket> strPkt)
{
	// Load bullet prefabs
	/*if (weapons.Load(game, gameConfig, audioEngine) == false)
		return false;*/

	if (ball.Load(game, gameConfig, strPkt, audioEngine) == false)
		return false;
	// Load the player entities
	if (players.Load(game, gameConfig, strPkt, audioEngine) == false)
		return false;
	// Load the enemy entities
	if (bricks.Load(game, gameConfig, strPkt) == false)
		return false;
	if (gems.Load(game, gameConfig, strPkt) == false)
		return false;
	if (balls.Load(game, gameConfig, strPkt) == false)
		return false;
	if (enemies.Load(game, gameConfig, audioEngine) == false)
		return false;

	return true;
}

bool Application::InitSystems(std::vector<GamePacket>* gamePkt, std::vector<GamePacket> strPkt, bool& reset)
{
	// connect systems to global ECS
	if (playerSystem.Init(game, gameConfig, immediateInput, bufferedInput, gamePads, audioEngine, eventPusher, gamePkt, currentLevel) == false)
		return false;

	if (levelSystem.Init(game, gameConfig, audioEngine, strPkt) == false)
		return false;

	if (resetSystem.Init(game, gameConfig, gamePkt, strPkt, immediateInput, bufferedInput, gamePads, reset) == false)
		return false;
	//if (vkRenderingSystem.Init(game, gameConfig, d3d11, window) == false)
		//return false;

	if (physicsSystem.Init(game, gameConfig, gamePkt, audioEngine) == false)
		return false;


	if (ballSystem.Init(game, gameConfig, gamePkt, immediateInput, bufferedInput, gamePads, reset, &levels, levelindex, currentScore, lifeScore) == false)
		return false;


	if (enemySystem.Init(game, gameConfig, eventPusher) == false)
		return false;

	ini::IniFile myini;
	myini.setMultiLineValues(true);
	myini.load("../FontData/SaveData.ini");
	highScore = myini["SaveData"]["highscore"].as<int>();

	return true;
}

bool Application::PauseSystems(bool fudge)
{
	// pause on systems to global ECS
	playerSystem.Activate(fudge);
	levelSystem.Activate(fudge);
	resetSystem.Activate(fudge);
	physicsSystem.Activate(fudge);
	ballSystem.Activate(fudge);
	enemySystem.Activate(fudge);

	return true;
}


bool Application::GameLoop()
{
	// compute delta time and pass to the ECS system
	static auto start = std::chrono::steady_clock::now();
	double elapsed = std::chrono::duration<double>(
		std::chrono::steady_clock::now() - start).count();
	start = std::chrono::steady_clock::now();
	// let the ECS system run
	return game->progress(static_cast<float>(elapsed));
}
bool Application::InitLevelData()
{
	levels.push_back(false); levels.push_back(false); levels.push_back(false);
	levels.push_back(false); levels.push_back(false); levels.push_back(false);
	GW::SYSTEM::GLog log; // handy for logging any messages/warning/errors begin loading level
	//log.Create("../LevelLoaderLog.txt"); //kept for testing purposes
	log.EnableConsoleLogging(true); // mirror output to the console
	log.Log("Start Program.");

	lvlData.LoadLevel("../MyGameLevel.txt", "../Models", log);


	for (int x = 0; x < lvlData.levelTransforms.size(); x++)
	{
		for (int y = 0; y < lvlData.nameInfo.size(); y++)
		{

			if (lvlData.levelTransforms[x].row4.x == lvlData.nameInfo[y].row4.x && lvlData.levelTransforms[x].row4.y == lvlData.nameInfo[y].row4.y &&
				lvlData.levelTransforms[x].row4.z == lvlData.nameInfo[y].row4.z && lvlData.levelTransforms[x].row4.w == lvlData.nameInfo[y].row4.w)
			{
				lvlData.names.push_back(lvlData.nameInfo[y].name);
				break;
			}

		}
	}

	for (int i = 0; i < lvlData.levelTransforms.size(); i++)
	{
		GamePacket temp = GamePacket(lvlData.levelTransforms[i], i, lvlData.names[i]); //assigning to world array
		collectionPack.startPacket.push_back(temp); //column is at index 4 //name "Column is at index 11, do not match
	}
	return true;
}
