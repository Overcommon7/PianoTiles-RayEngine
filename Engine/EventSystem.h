#pragma once

namespace RayEngine
{
	class Selectable;
	class GameObject;

	class EventSystem
	{
	public:
		GameObject* SelectedGameObject();
		GameObject* HoveredGameObject();

		const vector<Selectable*>& RaycastAll();
		static EventSystem* Get(size_t id = ULLONG_MAX);

#ifdef ENGINEDLL 
	public:
#else
	private:
#endif
		bool Select(Selectable* target);
		bool Hover(Selectable* target);
		void Update();
		void OnSceneUnloaded();

		~EventSystem()
		{
			currentSelectedGameObject = nullptr;
			currentHoveredGameObject = nullptr;
			lastHoveredGameObject = nullptr;
		}

		EventSystem(size_t sceneID) : sceneID(sceneID) {}

	private:
		Selectable* currentSelectedGameObject = nullptr;
		Selectable* currentHoveredGameObject = nullptr;
		Selectable* lastHoveredGameObject = nullptr;

		vector<Selectable*> raycastTargets = {};
		const size_t sceneID;


	};
}


