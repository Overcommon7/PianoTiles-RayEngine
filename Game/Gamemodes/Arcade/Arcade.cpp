#include "pch.h"
#include "Arcade.h"

#include "Tiles/TileManager.h"
#include "Gamestates/Retry.h"

void Arcade::OnStart()
{
	scoreDisplay = TextRenderer::Create("0", 35, RED);
	scoreDisplay->SetSortingLayer(100);
	scoreDisplay->Transform()->SetPosition({ (Base::Get()->GetData().screenWidth * 0.5f) - (scoreDisplay->Bounds().Size().x * 0.5f), 10});

	IGamemode::OnStart();
	score = 0;
	tilesPerSecond = 3;
}

void Arcade::OnEnd()
{
	IGamemode::OnEnd();
}

void Arcade::OnTileMissed()
{
	IGamemode::OnTileMissed();
}

void Arcade::OnUpdate()
{
	IGamemode::OnUpdate();
	if (!started) return;
	if (failed)	return;

	tilesPerSecond = std::min(tilesPerSecond + (speedUpPerSecond * Time::DeltaTime()), maxSpeed);
	float delta = tilesPerSecond * Time::DeltaTime() * Tile::SIZE.y;
	for (const auto& tile : tiles)
	{
		tile->Transform()->TranslateYPos(delta);
	}
}

void Arcade::OnTileClicked(Tile* tile)
{
	IGamemode::OnTileClicked(tile);
	++score;
	scoreDisplay->SetText(to_string(score));
	scoreDisplay->Transform()->SetXPosition((Base::Get()->GetData().screenWidth * 0.5f) - (scoreDisplay->Bounds().Size().x * 0.5f));
}

Arcade* Arcade::Get()
{
	if (!arcade)
		arcade = new Arcade();

	return arcade;
}

void Arcade::SetUpRetry()
{
	Base::Get()->SetClearColor(RED);
	Retry::OnStart(to_string(score), Name());
}

void Arcade::Shutdown()
{
	delete arcade;
}
