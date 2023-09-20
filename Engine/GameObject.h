#pragma once
#include "Object.h"
#include "Transform.h"
#include "Interfaces.h"
#include "Delegate.h"

namespace RayEngine
{
	class Component;

	class GameObject : public Object
	{
	public:

		static GameObject* Create(Vector2 position = {}, const short execultionPriority = 0, const string& name = "New GameObject", const string& sceneName = "");

		inline RayEngine::Transform* Transform() const { return transform; }
		void Destroy(Component* component);
		static void Destroy(GameObject* gameObject);
		inline const short ExecutionPriority() const { return execultionPriority; }
		void SetExecutionPriority(short priority);
		inline const string_view Tag() const { return tag; }
		inline void SetTag(const string& tag) { this->tag = tag; }
		inline bool CompareTag(const string& tag) { return this->tag == tag; }
		inline bool CompareTag(const string_view& tag) { return this->tag == tag; }


		inline const size_t SceneID() const { return sceneID; }		

		inline Delegate1<GameObject>& OnUpdate() { return onUpdate; }
		inline Delegate1<GameObject>& OnDraw() { return onDraw; }
		inline Delegate1<GameObject>& OnLateUpdate() { return onLateUpdate; }
		inline Delegate1<GameObject>& OnLateDraw() { return onLateDraw; }

		~GameObject()
		{
			for (auto component : components)
				delete component;

			components.clear();
			components.shrink_to_fit();
		}
#ifdef ENGINEDLL
		public:
#else 
		private:
#endif
		void Update();
		void Draw();
		void LateUpdate();
		void LateDraw();

	private:
		vector<Component*> components;
		vector<Component*> destoryQueries;

		RayEngine::Transform* transform;
		short execultionPriority;
		size_t sceneID;
		bool internallyActive = true;
		string tag = "Untagged";
		
		Delegate1<GameObject> onUpdate;
		Delegate1<GameObject> onDraw;
		Delegate1<GameObject> onLateUpdate;
		Delegate1<GameObject> onLateDraw;

		GameObject(Vector2 position, const short execultionPriority, const string& name, const size_t id);

	public:
		template<class ComponentType>
		inline ComponentType* GetComponent() const
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");

			for (auto component : components)
			{
				ComponentType* temp = dynamic_cast<ComponentType*>(component);
				if (temp != nullptr) return temp;
			}

			return nullptr;
		}

		template<class ComponentType>
		inline bool TryGetComponent(ComponentType*& result) const
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");

			result = GetComponent<ComponentType>();
			if (result == nullptr) return false;
			return true;
		}

		template<class ComponentType>
		inline vector<ComponentType*> GetComponents() const
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");

			vector<ComponentType*> values;
			for (auto component : components)
			{
				ComponentType* temp = dynamic_cast<ComponentType*>(component);
				if (temp != nullptr) values.push_back(temp);
			}

			return values;
		}
		template<class ComponentType, class... Args>
		inline ComponentType* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");
			ComponentType* component = std::construct_at(new ComponentType, this, args...);
			components.push_back(component);
			return component;
		}
		template<class ComponentType, class... Args>
		inline ComponentType* GetOrAddComponent(Args&&... args)
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");

			ComponentType* value = nullptr;
			if (TryGetComponent(value)) return value;

			return AddComponent<Component>(args);

		}

		template<class ComponentType>
		inline ComponentType* GetComponentInChildren(bool includeSelf = false) const
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");
			ComponentType* value = nullptr;
			if (includeSelf)
				if (TryGetComponent(value)) return value;

			for (int i = 0; i < transform->ChildCount(); i++)
				if (transform->GetChild(i)->GameObject()->TryGetComponent(value)) return value;

			return nullptr;
		}

		template<class ComponentType>
		inline vector<ComponentType*> GetComponentsInChildren(bool includeSelf = false) const
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");
			vector<ComponentType*> values = {};
			if (includeSelf)
			{
				vector<ComponentType*> temp = GetComponents<ComponentType>();
				for (ComponentType* component : temp)
					values.push_back(component);
			}


			for (int i = 0; i < transform->ChildCount(); i++)
			{
				auto child = transform->GetChild(i)->gameObject;
				vector<ComponentType*> temp = child->GetComponents<ComponentType>();
				for (ComponentType* component : temp)
					values.push_back(component);

				temp = child->GetComponentsInChildren<ComponentType>(includeSelf);
				for (ComponentType* component : temp)
					values.push_back(component);
			}

			return values;
		}
		GameObject(const GameObject& g) = delete;
		GameObject(const GameObject&& g) = delete;
		GameObject& operator=(const GameObject& g) = delete;
		GameObject& operator=(const GameObject&& g) = delete;
	};
}


