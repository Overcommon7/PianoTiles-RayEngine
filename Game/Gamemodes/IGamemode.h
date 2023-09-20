#pragma once
#include "Tiles/Tile.h"

class IGamemode
{
public:
	virtual const char* Name() = 0;
	virtual void OnStart();
	virtual void OnEnd();
	virtual void SetUpRetry() = 0;
	virtual void Shutdown() = 0;
	virtual void OnTileMissed();
	virtual void OnTileClicked(Tile* tile);

	virtual void OnTileOffScreen(Tile* tile);
	virtual void OnDraw();
	virtual void OnUpdate();
protected:
	bool started = false;
	bool failed = false;
	float failTimer = 0;
	inline static const float FAIL_TIME = 0.8f;
	vector<shared_ptr<Tile>> tiles = {};
	SpriteRenderer* redBox;
};