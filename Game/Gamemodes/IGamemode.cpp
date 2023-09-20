#include "pch.h"
#include "IGamemode.h"

#include "Tiles/TileManager.h"
#include "Base/App.h"


void IGamemode::OnTileOffScreen(Tile* tile)
{
	auto it = find_if(tiles.begin(), tiles.end(), [tile](const shared_ptr<Tile>& ptr) {
		return ptr.get() == tile;
		});

	if (it == tiles.end()) return;

	tiles.erase(it);
}

void IGamemode::OnDraw()
{
	auto& data = Base::Get()->GetData();

	for (int x = Tile::SIZE.x; x < data.screenWidth - 1; x += Tile::SIZE.x)
		DrawLine(x, 0, x, data.screenHeight, BLACK);
}

void IGamemode::OnUpdate()
{
	if (failed)
	{
		failTimer += Time::DeltaTime();
		if (failTimer < FAIL_TIME) return;

		SetUpRetry();
		App::SetGamestate(App::Gamestate::Retry);
		return;
	}

	if (!Mouse::IsLeftClicked() && !Mouse::IsRightClicked()) return;
	if (EventSystem::Get().HoveredGameObject() != nullptr) return;
	for (auto tile : tiles)
	{
		if (tile.get()->Collider()->IsColliding(Mouse::Position()))
			return;
	}

	failed = true;
	failTimer = 0;
	auto width = Base::Get()->GetData().screenWidth;
	auto y = Mouse::Position().y;
	auto it = std::find_if(tiles.begin(), tiles.end(), [width, y](const shared_ptr<Tile>& tile) {

		const Collider* collider = tile.get()->Transform()->GameObject()->GetComponent<Button>()->GetCollider();
		for (float i = 1; i < width; i += Tile::SIZE.x)
		{
			Vector2 point = { i, y };
			if (collider->IsColliding(point))
				return true;
		}
		return false;
	});

	if (it == tiles.end()) return;

	Vector2 position = { int(Mouse::Position().x / Tile::SIZE.x) * Tile::SIZE.x, (*it)->Transform()->Position().y };
	redBox->Transform()->SetPosition(position);
	redBox->GameObject()->SetActive(true);
}

void IGamemode::OnStart()
{
	Base::Get()->SetClearColor(WHITE);
	started = false;
	failed = false;
	tiles.clear();
	tiles = TileManager::SpawnStartingTiles();
	redBox = GameObject::Create()->AddComponent<SpriteRenderer>(Shape::Square, Tile::SIZE, RED, 10);
	redBox->GameObject()->SetActive(false);
}

void IGamemode::OnEnd()
{
	tiles.clear();
}

void IGamemode::OnTileMissed()
{
	failed = true;
	failTimer = 0;

	for (const auto& tile : tiles)
	{
		tile->Transform()->TranslateYPos(-Tile::SIZE.y);
	}

	redBox->GameObject()->SetActive(true);
	redBox->Transform()->SetPosition(tiles.front()->Transform()->Position());
}

void IGamemode::OnTileClicked(Tile* tile)
{
	if (failed)	return;

	auto it = find_if(tiles.begin(), tiles.end(), [tile](const shared_ptr<Tile>& ptr) {
		return ptr.get() == tile;
		});

	if (it == tiles.end()) return;
	if (!TileManager::OnTileClicked(tile)) return;

	started = true;
	tiles.push_back(TileManager::SpawnTile());
}
