#include "pch.h"
#include "GameTime.h"

void RayEngine::Time::Update()
{
    dt = GetFrameTime();
    now += dt;
}
