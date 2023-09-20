#pragma once
#include "Component.h"
#include "Delegate.h"
#include "Interfaces.h"

namespace RayEngine
{
	class BoxCollider;
	class Transform;
	class GameObject;

	class Scrollview : public Component, public IUpdate
	{
	public:
		Scrollview() = default;
		Scrollview(RayEngine::GameObject* gameObject, Vector2 size, float scrollSpeed);
		Scrollview(RayEngine::GameObject* gameObject, Vector2 size, const vector<RayEngine::Transform*>& items, float scrollSpeed);
		Delegate1<Scrollview>& GetItemAddedEvent() { return onItemAdded; }

		void AddItem(RayEngine::Transform* item);
		void AddItems(const vector<RayEngine::Transform*>& items);
		void SetSize(Vector2 size);
		
		static Scrollview* Create(Vector2 size, float scrollSpeed = 10.f, const vector<RayEngine::Transform*>& items = {});
	private:
		Delegate1<Scrollview> onItemAdded;
		BoxCollider* viewport;
		BoxCollider* content;
		float scrollSpeed;

		void Update() override;
		void UpdateViewables();
	};
}
