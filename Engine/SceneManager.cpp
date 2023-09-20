#include "pch.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "Scene.h"

#include "EventSystem.h"

size_t RayEngine::SceneManager::CreateScene(const string& name)
{
	scenes.push_back(new Scene(name));
	return scenes.back()->ID();
}

void RayEngine::SceneManager::LoadScene(const string& name)
{
	size_t id = GetSceneID(name);
	if (id != ULLONG_MAX)
		LoadScene(id);
}

void RayEngine::SceneManager::LoadScene(size_t id)
{
	auto it = GetScene(id);
	if (it == scenes.end()) return;
	if (*it == currentScene) return;

	currentScene = *it;
	if (!currentScene->IsFirstUpdate())
		sceneTransitionFrame = true;

	currentScene->SetFirstUpdate(true);	
}

void RayEngine::SceneManager::DestroyGameObject(GameObject* object, size_t sceneID)
{
	auto it = GetScene(sceneID);
	if (it == scenes.end())	return;

	(*it)->DestroyGameObject(object);
}

RayEngine::GameObject* RayEngine::SceneManager::CreateGameObject(GameObject* gameObject, string sceneName)
{
	if (scenes.empty() || currentScene == nullptr)
	{
		CreateScene("SampleScene");
		LoadScene("SampleScene");
	}
	


	if (sceneName.empty())
	{
		if (sceneTransitionFrame)
			return transtionalGameObjects.emplace_back(gameObject);
		return currentScene->AddGameObject(gameObject);
	}
		
	auto it = GetScene(sceneName);
	if (it == scenes.end()) return nullptr;

	return (*it)->AddGameObject(gameObject);

}

void RayEngine::SceneManager::UnloadScene(size_t id)
{
	if (id == ULLONG_MAX)
		id = CurrentSceneID();
	auto it = GetScene(id);
	if (it == scenes.end()) return;

	unloadQuries.push_back(*it);
}

void RayEngine::SceneManager::CloseScene()
{
	currentScene = nullptr;
}

void RayEngine::SceneManager::Update()
{
	if (currentScene == nullptr || sceneTransitionFrame)
		return;
	currentScene->Update();
}

void RayEngine::SceneManager::LateUpdate()
{
	if (currentScene && !sceneTransitionFrame)
		currentScene->LateUpdate();

	InternalUnload();
	sceneTransitionFrame = false;
	MoveTransitionalGameObjects();
}

void RayEngine::SceneManager::Draw()
{
	if (currentScene == nullptr || sceneTransitionFrame)
		return;
	currentScene->Draw();
}

void RayEngine::SceneManager::LateDraw()
{
	if (currentScene == nullptr || sceneTransitionFrame)
		return;
	currentScene->LateDraw();
}

void RayEngine::SceneManager::Shutdown()
{
	for (auto scene : scenes)
		delete scene;

	currentScene = nullptr;
	scenes.clear();
	scenes.shrink_to_fit();
}

void RayEngine::SceneManager::SetPriority(GameObject* object)
{
	auto scene = GetScene(object->SceneID());
	if (scene != scenes.end())
		(*scene)->SetFirstUpdate(true);
}

size_t RayEngine::SceneManager::GetSceneID(const string& name)
{
	auto it = GetScene(name);
	if (it == scenes.end())	return ULLONG_MAX;
	return (*it)->ID();
}

size_t RayEngine::SceneManager::CurrentSceneID()
{
	return currentScene ? currentScene->ID() : 0;
}

void RayEngine::SceneManager::PauseScene(size_t id)
{
		
}

string_view RayEngine::SceneManager::GetSceneName(size_t id)
{
	auto it = GetScene(id);
	if (it == scenes.end())	return "";
	return (*it)->Name();
}

RayEngine::EventSystem& RayEngine::SceneManager::GetCurrentSceneEventSystem()
{
	return currentScene->GetEventSystem();
}

vector<RayEngine::Scene*>::iterator RayEngine::SceneManager::GetScene(const string& name)
{
	return std::find_if(scenes.begin(), scenes.end(), [&name](const Scene* s)
		{
			return s->Name() == name;
		});

}

vector<RayEngine::Scene*>::iterator RayEngine::SceneManager::GetScene(size_t id)
{
	return std::find_if(scenes.begin(), scenes.end(), [&id](const Scene* s)
		{
			return s->ID() == id;
		});
}

void RayEngine::SceneManager::InternalUnload()
{
	if (unloadQuries.empty()) return;

	for (auto scene : unloadQuries)
		scene->Unload();

	unloadQuries.clear();
}

void RayEngine::SceneManager::MoveTransitionalGameObjects()
{
	if (transtionalGameObjects.empty()) return;

	for (auto obj : transtionalGameObjects)
		currentScene->AddGameObject(obj);

	transtionalGameObjects.clear();
}
