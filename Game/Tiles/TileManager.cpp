#include "pch.h"
#include "TileManager.h"

shared_ptr<Tile> TileManager::SpawnTile()
{
	auto position = V2(GetRandomPosition(), tiles.front()->Transform()->Position().y - Tile::SIZE.y);
	return tiles.insert(tiles.begin(), std::make_shared<Tile>(position)).operator*();
}

const vector<shared_ptr<Tile>>& TileManager::SpawnStartingTiles(int amount)
{
	V2 position = { 0, -Tile::SIZE.y * (amount - 4) };
	for (int i = 0; i < amount; i++)
	{
		position.x = GetRandomPosition();
		tiles.push_back(std::make_shared<Tile>(position));
		position.y += Tile::SIZE.y;	
	}
	
	start->GameObject()->SetActive(true);
	start->Transform()->SetPosition({ position.x + 10, position.y - (Tile::SIZE.y * 0.5f) });

	return tiles;
}

void TileManager::SetProMode(bool pro)
{
	proMode = pro;
}

bool TileManager::OnTileClicked(Tile* tile)
{
	if (tile != tiles.back().get()) return false;

	start->GameObject()->SetActive(false);
	tile->SetClicked();
	tiles.pop_back();

	return true;
}

void TileManager::OnStart()
{
	tiles.clear();
	tiles.reserve(20);
	lastPosition = -1;
}

void TileManager::OnEnd()
{
	tiles.clear();
}

void TileManager::Init()
{
	start = TextRenderer::Create("Start");
	start->SetColor(WHITE);
	start->SetSortingLayer(1000);
	start->GameObject()->SetActive(false);
}

float TileManager::GetRandomPosition()
{
	auto temp = Random(3);
	if (!proMode) return Tile::SIZE.x * temp;

	while (temp == lastPosition)
		temp = Random(3);

	lastPosition = temp;
	return Tile::SIZE.x * temp;
	
}

