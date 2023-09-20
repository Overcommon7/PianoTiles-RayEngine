#pragma once
#include "Gamemodes/IGamemode.h"

class Arcade final : public IGamemode 
{
public:
    void OnStart() override;
    void OnEnd() override;
    void Shutdown() override;
    void OnTileMissed() override;
    void OnTileClicked(Tile* tile) override;
    void SetUpRetry() override;
    void OnUpdate() override;
   

    inline const char* Name() override { return "Aracde"; }
    static Arcade* Get();
private:
    inline static Arcade* arcade = nullptr;


    TextRenderer* scoreDisplay = nullptr;
    int score = 0;
    float tilesPerSecond = 3;
    const float speedUpPerSecond = 0.075f;
    const float maxSpeed = 5.15f;

    Arcade() = default;
public:
    
    Arcade(const Arcade& a) = delete;
    Arcade(const Arcade&& a) = delete;
    Arcade& operator=(const Arcade& a) = delete;
    Arcade& operator=(const Arcade&& a) = delete;

   
};

