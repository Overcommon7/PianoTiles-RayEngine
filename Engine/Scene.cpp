#include "pch.h"
#include "Scene.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "EventSystem.h"

RayEngine::Scene::Scene(const string& name, size_t capacity) 
	: name(name), id(Random(ULLONG_MAX - 1)), firstUpdate(true)
{
	objects.reserve(capacity);
	eventSystem = new EventSystem(id);
}

void RayEngine::Scene::Unload()
{
	eventSystem->OnSceneUnloaded();

	delete eventSystem;
	eventSystem = nullptr;

	for (auto object : objects)
	{
		delete object;
	}
		
	objects.clear();
	if (objects.capacity() < 300)
		objects.reserve(300);

	
}


void RayEngine::Scene::Update()
{
	if (firstUpdate)
	{
		std::sort(objects.begin(), objects.end(), [](const GameObject* g1, const GameObject* g2) {
			return g1->ExecutionPriority() < g2->ExecutionPriority();
			});

		firstUpdate = false;
	}
		
	if (!eventSystem)
		eventSystem = new EventSystem(id);

	eventSystem->Update();

	auto size = objects.size();
	for (int i = 0; i < size; ++i)
		objects[i]->Update();

	bool added = size < objects.size();

	if (!destoryQueries.empty())
	{
		objects.erase(std::remove_if(objects.begin(), objects.end(), [this](const GameObject* x) {
			return std::find(destoryQueries.begin(), destoryQueries.end(), x) != destoryQueries.end();
			}), objects.end());

		for (auto obj : destoryQueries)
			delete obj;

		destoryQueries.clear();
	}

	if (added)
	{
		std::sort(objects.begin(), objects.end(), [](const GameObject* const g1, const GameObject* const g2) {
			return g1->ExecutionPriority() < g2->ExecutionPriority();
			});
	}
}

void RayEngine::Scene::LateUpdate()
{
	auto size = objects.size();
	for (int i = 0; i < size; ++i)
		objects[i]->LateUpdate();

	bool added = size < objects.size();

	if (!destoryQueries.empty())
	{
		objects.erase(std::remove_if(objects.begin(), objects.end(), [this](const GameObject* const x) {
			return std::find(destoryQueries.begin(), destoryQueries.end(), x) != destoryQueries.end();
			}), objects.end());

		for (auto obj : destoryQueries)
			delete obj;

		destoryQueries.clear();
	}

	if (added)
	{
		std::sort(objects.begin(), objects.end(), [](const GameObject* const g1, const GameObject* const g2) {
			return g1->ExecutionPriority() < g2->ExecutionPriority();
			});
	}

	
}

void RayEngine::Scene::Draw()
{
	for (auto object : objects)
		object->Draw();
}

void RayEngine::Scene::LateDraw()
{
	for (auto object : objects)
		object->LateDraw();
}

RayEngine::GameObject* RayEngine::Scene::AddGameObject(RayEngine::GameObject* gameObject)
{
	objects.push_back(gameObject);
	return objects.back();
}

void RayEngine::Scene::DestroyGameObject(GameObject* gameObject)
{
	if (SceneManager::IsCurrentScene(this))
	{
		if (find(destoryQueries.begin(), destoryQueries.end(), gameObject) != destoryQueries.end()) return;
		destoryQueries.push_back(gameObject);
	}	
	else
	{
		auto it = find(objects.begin(), objects.end(), gameObject);
		if (it != objects.end())
		{
			delete* it;
			objects.erase(it);
		}
			
	}
}

RayEngine::Scene::~Scene()
{
	delete eventSystem;
	eventSystem = nullptr;

	for (auto object : objects)
		delete object;

	objects.clear();
	objects.shrink_to_fit();

	
}		
