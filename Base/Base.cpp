#include "pch.h"
#include "Base.h"

#include "GameTime.h"
#include "Mouse.h"
#include "Keyboard.h"

using namespace RayEngine;

void Base::Run(const Data& data, const vector<function<void()>>& initializers, const vector<function<void()>>& update, const vector<function<void()>>& draw, const vector<function<void()>>& shutdown)
{
	this->data = new Data(data);
	Initialize(initializers);
	Update(update, draw);
	Shutdown(shutdown);
}

Base* Base::Get()
{
	static RayEngine::Base base = RayEngine::Base();
	return &base;
}

void Base::Initialize(const vector<function<void()>>& initializers)
{
	InitWindow(data->screenWidth, data->screenHeight, data->title.c_str());
	drawFont = new Font();
	*drawFont = GetFontDefault();
	if (data->targetFPS < 0)
	{
		data->targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());
	}
	SetTargetFPS(data->targetFPS);
	InitAudioDevice();

	for (const auto& inits : initializers)
		inits();
}

void Base::Update(const vector<function<void()>>& update, const vector<function<void()>>& draw)
{
	while (!WindowShouldClose())
	{
		Time::Update();
		Mouse::Update();
		Keyboard::Update();

		for (const auto& updates : update)
			updates();

		BeginDrawing();
		ClearBackground(data->clearColor);
		for (const auto& draws : draw)
			draws();

		if (data->debugDraw)
			DrawFPS(5, 5);

		EndDrawing();
	}
}

void Base::Shutdown(const vector<function<void()>>& shutdown)
{
	for (const auto& shutdowns : shutdown)
		shutdowns();

	delete data;
	CloseAudioDevice();
	CloseWindow();
}
