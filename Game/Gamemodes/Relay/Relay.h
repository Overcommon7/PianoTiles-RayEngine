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
	inline const char* Name() override { return "Relay"; }

	static Relay* Get();
private:
	inline static Relay* rush = nullptr;
};

