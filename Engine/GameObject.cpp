#include "pch.h"
#include "GameObject.h"

#include "Transform.h"
#include "Interfaces.h"

#include "SceneManager.h"

namespace
{
	template<class T, class H> 
	static void DestroyFromVector(vector<T*>& entries, vector<H*>& queries)
	{
		auto it = entries.begin();

		while (it != entries.end())
		{
			T* ptr = *it;
			for (auto query : queries)
			{
				if (ptr == dynamic_cast<T*>(query))
				{
					it = entries.erase(it);
					break;
				}
			}
			++it;
		}
	}
}

void RayEngine::GameObject::SetExecutionPriority(short priority)
{
	execultionPriority = priority;
	SceneManager::SetPriority(this);
}

RayEngine::GameObject::GameObject(Vector2 position, const short execultionPriority, const string& name, const size_t id)
	: Object(name), execultionPriority(execultionPriority)
{
	if (id == ULLONG_MAX) sceneID = SceneManager::CurrentSceneID();
	else sceneID = id;

	transform = new RayEngine::Transform(this, position);	
}

void RayEngine::GameObject::Destroy(GameObject* gameObject)
{
	for (int i = 0; i < gameObject->transform->ChildCount(); i++)
		Destroy(gameObject->transform->GetChild(i)->GameObject());

	SceneManager::DestroyGameObject(gameObject, gameObject->sceneID);
}

void RayEngine::GameObject::Destroy(Component* component)
{
	auto it = find(components.begin(), components.end(), component);
	if (it == components.end())	return;
	if (typeid(*(*it)) == typeid(RayEngine::Transform))
	{
		Destroy(this);
		return;
	}		

	destoryQueries.push_back(component);
	
		
}

RayEngine::GameObject* RayEngine::GameObject::Create(Vector2 position, const short execultionPriority, const string& name, const string& sceneName)
{
	return SceneManager::CreateGameObject(new GameObject(position, execultionPriority, name, SceneManager::GetSceneID(sceneName)), sceneName);
}

void RayEngine::GameObject::Update()
{
	if (!isActive) return;
	internallyActive = true;

	const RayEngine::Transform* parent = transform->Parent();
	while (parent)
	{
		if (!parent->GameObject()->isActive)
		{
			internallyActive = false;
			return;
		}
		parent = parent->Parent();
	}
		

	for (auto component : components)
	{
		if (!component->IsActive())	continue;

		auto update = dynamic_cast<IUpdate*>(component);
		if (update != nullptr) update->Update();
	}

	onUpdate.Invoke(*this);

	if (!destoryQueries.empty())
	{
		components.erase(std::remove_if(components.begin(), components.end(), [this](const Component* x) {
			return std::find(destoryQueries.begin(), destoryQueries.end(), x) != destoryQueries.end();
			}), components.end());

		for (auto obj : destoryQueries)
			delete obj;

		destoryQueries.clear();
	}	
}

void RayEngine::GameObject::Draw()
{
	if (!isActive) return;
	if (!internallyActive) return;

	for (auto component : components)
	{
		if (!component->IsActive()) continue;

		auto draw = dynamic_cast<IDraw*>(component);
		if (draw != nullptr) draw->Draw();
	}

	onDraw.Invoke(*this);
}

void RayEngine::GameObject::LateUpdate()
{
	if (!isActive) return;
	if (!internallyActive) return;

	for (auto component : components)
	{
		if (!component->IsActive())	continue;

		auto update = dynamic_cast<ILateUpdate*>(component);
		if (update != nullptr) update->LateUpdate();
	}

	onLateUpdate.Invoke(*this);

	if (!destoryQueries.empty())
	{
		components.erase(std::remove_if(components.begin(), components.end(), [this](const Component* x) {
			return std::find(destoryQueries.begin(), destoryQueries.end(), x) != destoryQueries.end();
			}), components.end());

		for (auto obj : destoryQueries)
			delete obj;

		destoryQueries.clear();
	}
}

void RayEngine::GameObject::LateDraw()
{
	if (!isActive) return;
	if (!internallyActive) return;

	for (auto component : components)
	{
		if (!component->IsActive()) continue;

		auto draw = dynamic_cast<ILateDraw*>(component);
		if (draw != nullptr) draw->LateDraw();
	}

	onLateDraw.Invoke(*this);
}


