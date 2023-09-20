#include "pch.h"
#include "Classic.h"

void Classic::OnStart()
{
}

void Classic::OnEnd()
{
}

void Classic::Shutdown()
{
}

Classic* Classic::Get()
{
	if (!classic)
		classic = new Classic();

	return classic;
}

void Classic::SetUpRetry()
{
}

void Classic::OnTileMissed()
{
	IGamemode::OnTileMissed();
}

void Classic::OnTileClicked(Tile* tile)
{
	IGamemode::OnTileClicked(tile);
}
