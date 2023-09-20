#include "pch.h"
#include "Relay.h"

void Relay::OnStart()
{
	IGamemode::OnStart();
}

void Relay::OnEnd()
{
	IGamemode::OnEnd();
}

Relay* Relay::Get()
{
	if (!rush)
		rush = new Relay();
	return rush;
}

void Relay::SetUpRetry()
{

}

void Relay::Shutdown()
{
	delete rush;
}

void Relay::OnTileMissed()
{
	IGamemode::OnTileMissed();
}

void Relay::OnTileClicked(Tile* tile)
{
	IGamemode::OnTileClicked(tile);
}
