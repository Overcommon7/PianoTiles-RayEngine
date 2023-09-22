#pragma once
#include "Gamemodes/IGamemode.h"
class Relay: public IGamemode
{
public:
	void OnStart() override;
	void OnEnd() override;
	void Shutdown() override;
	void OnTileMissed() override;
	void OnTileClicked(Tile* tile) override;
	void SetUpRetry() override;
	void OnUpdate() override;
	inline const char* Name() override { return "Relay"; }

	static Relay* Get();
	static inline const int TILES_TO_REFRESH = 45;
	static inline const float TIME = 12.f;
	static inline const float REFRESH_TIME = 1.5f;

	float timer = 0;
	int tilesPressed = 0;
	int totalTiles = 0;
	bool showRefresh = false;
	float refreshTimer = 0;
	

	TextRenderer* timeOut;
	TextRenderer* timerDisplay;
	TextRenderer* refreshDisplay;
	SpriteRenderer* scoreDisplay;
private:
	inline static Relay* rush = nullptr;
};

