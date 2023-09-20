#include "pch.h"
#include "System.h"

#include "SceneManager.h"
#include "SpriteRenderer.h"

namespace
{
	inline void Initialize()
	{
		
	}

	inline void Update()
	{
		RayEngine::SceneManager::Update();
		RayEngine::SceneManager::LateUpdate();
	}

	inline void Draw()
	{
		RayEngine::SceneManager::Draw();
		RayEngine::Renderer::StaticDraw();
		RayEngine::SceneManager::LateDraw();
	}

	inline void Shutdown()
	{
		RayEngine::SceneManager::Shutdown();
		RayEngine::SpriteRenderer::Shutdown();
	}
}

RayEngine::System* RayEngine::System::Get()
{
	static System sys = System();
	return &sys;
}

void RayEngine::System::Run(const Base::Data& data, vector<function<void()>> initializers, vector<function<void()>> update, vector<function<void()>> draw, vector<function<void()>> shutdown)
{
	update.push_back(Update);
	draw.push_back(Draw);
	shutdown.push_back(Shutdown);
	Base::Get()->Run(data, initializers, update, draw, shutdown);
}
