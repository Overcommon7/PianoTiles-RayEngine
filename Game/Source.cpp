#include "pch.h"
#include "Base/App.h"

#include "Tiles/Tile.h"

int main()
{
	RayEngine::Base::Data data = RayEngine::Base::Data(fs::current_path());
	data.debugDraw = true;
	data.clearColor = WHITE;
	data.screenHeight = Tile::SIZE.y * 4;
	data.screenWidth = Tile::SIZE.x * 4;
	data.title = "PianoTiles";

	vector<function<void()>> initializers = { App::Init };
	vector<function<void()>> update = { App::Update };
	vector<function<void()>> draw = { App::Draw };
	vector<function<void()>> shutdown = { App::Shutdown };
	
	RayEngine::System::Get()->Run(data, initializers, update, draw, shutdown);
}
