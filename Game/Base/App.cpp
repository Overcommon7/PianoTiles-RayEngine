#include "pch.h"
#include "App.h"

#include "Gamemodes/Arcade/Arcade.h"
#include "Gamemodes/Relay/Relay.h"
#include "Gamemodes/Classic/Classic.h"

#include "Gamestates/Titlescreen.h"
#include "Gamestates/Controls.h"
#include "Gamestates/Retry.h"

#include "Tiles/TileManager.h"

void App::Init()
{
	TextRenderer::SetDefaultFont(LoadFont("CandaraBold.ttf"));

	for (int i = 0; i <= (int)Gamemode::Relay; i++)
		gamemodeNames.insert({ (Gamemode)i, magic_enum::enum_name((Gamemode)i).data() });

	SceneManager::CreateScene(Titlescreen::NAME);
	SceneManager::CreateScene(Controls::NAME);
	SceneManager::CreateScene(Retry::NAME);

	SceneManager::CreateScene(Arcade::Get()->Name());
	SceneManager::CreateScene(Relay::Get()->Name());
	SceneManager::CreateScene(Classic::Get()->Name());

	TileManager::Init();

	SceneManager::LoadScene(Titlescreen::NAME);
	Titlescreen::Init();

	SceneManager::LoadScene(Controls::NAME);
	Controls::Init();

	SceneManager::LoadScene(Retry::NAME);
	Retry::Init();

	SceneManager::LoadScene(Arcade::Get()->Name());
	gamemodes.insert({ Gamemode::Arcade, Arcade::Get() });

	SceneManager::LoadScene(Relay::Get()->Name());
	gamemodes.insert({ Gamemode::Relay, Relay::Get() });

	SceneManager::LoadScene(Classic::Get()->Name());
	gamemodes.insert({ Gamemode::Classic, Classic::Get() });	

	SceneManager::LoadScene(Titlescreen::NAME);
}

void App::Shutdown()
{
	for (const auto& [gamemode, pointer] : gamemodes)
		pointer->Shutdown();

	Titlescreen::Shutdown();
	Controls::Shutdown();
}

void App::Draw()
{
	if (currentGamestate == Gamestate::Gameplay && currentGamemode != Gamemode::None)
		gamemodes[currentGamemode]->OnDraw();
}

void App::Update()
{
	if (currentGamestate == Gamestate::Gameplay && currentGamemode != Gamemode::None)
		gamemodes[currentGamemode]->OnUpdate();
}

void App::LoadGamemode(Gamemode gamemode)
{
	if (currentGamemode != Gamemode::None) {
		gamemodes[currentGamemode]->OnEnd();
		TileManager::OnEnd();
		SceneManager::UnloadScene(SceneManager::GetSceneID(gamemodes[currentGamemode]->Name()));
		++debug;
	}

	currentGamemode = gamemode;
	
	if (currentGamemode != Gamemode::None)
	{
		SceneManager::LoadScene(gamemodes[currentGamemode]->Name());
		SetGamestate(Gamestate::Gameplay);
		TileManager::OnStart();
		gamemodes[currentGamemode]->OnStart();
	}
}

void App::SetGamestate(Gamestate state)
{
	switch (state)
	{
	case App::Gamestate::Titlescreen:
		Base::Get()->SetClearColor(WHITE);
		LoadGamemode(Gamemode::None);
		SceneManager::LoadScene(Titlescreen::NAME);
		break;
	case App::Gamestate::Controls:
		LoadGamemode(Gamemode::None);
		SceneManager::LoadScene(Controls::NAME);
		break;
	case App::Gamestate::Retry:
		SceneManager::LoadScene(Retry::NAME);
	}

	currentGamestate = state;
}

IGamemode* App::GetCurrentGamemodeManager()
{
	if (currentGamemode == Gamemode::None)
		return nullptr;
	return gamemodes[currentGamemode];
}

vector<string*> App::GetGamemodeNames()
{
	vector<string*> names;
	for (auto& [gamemode, name] : gamemodeNames)
		names.push_back(&name);
	return names;
}

const string* const App::GetGamemodeName(Gamemode gamemode)
{
	return &gamemodeNames[gamemode];
}
