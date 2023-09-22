#pragma once
#include "GameObject.h"

namespace RayEngine
{
	class EventSystem;
	class Component;

	class Scene
	{
		const string name;
		const size_t id;
		EventSystem* eventSystem = nullptr;
		vector<RayEngine::GameObject*> objects;
		vector<RayEngine::GameObject*> destoryQueries = {};
		bool firstUpdate = true;

	public:
		constexpr string_view Name() const { return name; }
		constexpr size_t ID() const { return id; }
		
		template<class ComponentType>
		inline ComponentType* GetObjectOfType()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");

			ComponentType* component = nullptr;
			for (GameObject* object : objects)
			{
				if (object->TryGetComponent<ComponentType>(component))
					return component;
			}

			return nullptr;
		}

		template<class ComponentType>
		inline vector<ComponentType*> GetObjectsOfType()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "Must be of type Component");

			vector<ComponentType*> components = {};
			for (GameObject* object : objects)
			{
				ComponentType* component = nullptr;
				if (object->TryGetComponent<ComponentType>(component))
					components.push_back(component);
			}

			return components;
		}
#ifdef ENGINEDLL 
	public:
#else
	private:
#endif
		Scene(const string& name, size_t capacity = 300);

		void Unload();
		void Update();
		void LateUpdate();
		void Draw();
		void LateDraw();
		GameObject* AddGameObject(GameObject* gameObject);
		void DestroyGameObject(GameObject* gameObject);
		inline EventSystem* GetEventSystem() const { return eventSystem; };

		void SetFirstUpdate(bool update) { firstUpdate = update; }
		bool IsFirstUpdate() const { return firstUpdate; }
		

		~Scene();
	};
}


