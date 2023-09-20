#pragma once
#include "Gamemodes/IGamemode.h"

class Classic : public IGamemode
{
public:
	void OnStart() override;
	void OnEnd() override;
	void Shutdown() override;
	void OnTileMissed() override;
	void OnTileClicked(Tile* tile) override;
	void SetUpRetry() override;
	inline const char* Name() override { return "Classic"; }

	static Classic* Get();
private:
	inline static Classic* zen = nullptr;

	

};

