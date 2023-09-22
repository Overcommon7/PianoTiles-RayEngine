#include "pch.h"
#include "EventSystem.h"

#include "Selectable.h"
#include "GameObject.h"

#include "SceneManager.h"
#include "Collider.h"

RayEngine::GameObject* RayEngine::EventSystem::SelectedGameObject()
{
	if (currentSelectedGameObject)
		return currentSelectedGameObject->GameObject();
	return nullptr;
}

RayEngine::GameObject* RayEngine::EventSystem::HoveredGameObject()
{
	if (currentHoveredGameObject)
		return currentHoveredGameObject->GameObject();
	return nullptr;
}

const vector<RayEngine::Selectable*>& RayEngine::EventSystem::RaycastAll()
{
	return raycastTargets;
}

bool RayEngine::EventSystem::Select(Selectable* target)
{

	if (target)
	{
		if (target->GameObject()->SceneID() == sceneID)
		currentSelectedGameObject = target;
	}	
	else currentSelectedGameObject = nullptr;
	return true;
}

bool RayEngine::EventSystem::Hover(Selectable* target)
{
	if (!target)
	{
		currentHoveredGameObject = nullptr;
		return false;
	}

	if (!target->IsRayCastTarget())	return false;
	if (target->GameObject()->SceneID() != sceneID) return false;
	currentHoveredGameObject = raycastTargets.emplace_back(target);
	return true;
}

RayEngine::EventSystem* RayEngine::EventSystem::Get(size_t id)
{
	if (id == ULLONG_MAX)
		return SceneManager::GetCurrentSceneEventSystem();
	return SceneManager::GetEventSystem(id);
}

void RayEngine::EventSystem::Update()
{
	Selectable* selectable;
	if (!raycastTargets.empty() && raycastTargets.back())
	{
		selectable = raycastTargets.back();
		if (lastHoveredGameObject != currentHoveredGameObject)
		{
			if (lastHoveredGameObject) lastHoveredGameObject->SetHovered(false);
			selectable->SetHovered(true);
		}
		else if (!selectable->IsHovered()) selectable->SetHovered(true);
		
		selectable->timeInCollider += Time::DeltaTime();
	}
	else
	{
		if (currentHoveredGameObject)
		{
			currentHoveredGameObject->SetHovered(false);
		}
			
		currentHoveredGameObject = nullptr;
	}

	lastHoveredGameObject = currentHoveredGameObject;
		

	if (Mouse::IsLeftClicked() || Mouse::IsRightClicked())
	{
		bool right = !Mouse::IsLeftClicked() && Mouse::IsRightClicked();

		if (currentSelectedGameObject)
		{	
			if (right &&
				!raycastTargets.empty() &&
				raycastTargets.back() &&
				!raycastTargets.back()->AcceptsRightClicks())
			{
				return;
			}
				

			selectable = currentSelectedGameObject;
			if (!selectable->GetCollider()->IsColliding(Mouse::Position()))	
			{
				currentSelectedGameObject->SetSelected(false);
				currentSelectedGameObject = nullptr;

				if (!raycastTargets.empty())
				{
					raycastTargets.back()->SetSelected(true);
					currentSelectedGameObject = raycastTargets.back();
				}
			}
			else if (!raycastTargets.empty())
			{
			   raycastTargets.back()->SetSelected(true);
			}
			
		}
		else if (!raycastTargets.empty())
		{
			raycastTargets.back()->SetSelected(true);
			currentSelectedGameObject = raycastTargets.back();
		}

	}

	
	raycastTargets.clear();
		
}

void RayEngine::EventSystem::OnSceneUnloaded()
{
	raycastTargets.clear();
	currentSelectedGameObject = nullptr;
	lastHoveredGameObject = nullptr;
	currentHoveredGameObject = nullptr;
}
