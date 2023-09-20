#pragma once
#include "Tile.h"

class TileManager
{
public:
    static shared_ptr<Tile> SpawnTile();
    static const vector<shared_ptr<Tile>>& SpawnStartingTiles(int amount = 6);
    static void SetProMode(bool pro);
    inline static bool IsProMode() { return proMode; }
    static bool OnTileClicked(Tile* tile);

    static void OnStart();
    static void OnEnd();
    static void Init();
private:
    inline static bool proMode = false;
    inline static vector<shared_ptr<Tile>> tiles = {};
    inline static int lastPosition = -1;
    static float GetRandomPosition();

    inline static TextRenderer* start = nullptr;
public:
    TileManager() = delete;
    TileManager(const TileManager& t) = delete;
    TileManager(const TileManager&& t) = delete;
    TileManager& operator=(const TileManager& t) = delete;
    TileManager& operator=(const TileManager&& t) = delete;
};

