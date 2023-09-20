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
		static EventSystem& Get();

#ifdef ENGINEDLL 
	public:
#else
	private:
#endif
		bool Select(Selectable* target);
		bool Hover(Selectable* target);
		void Update();
		void OnSceneUnloaded();

	private:
		Selectable* currentSelectedGameObject;
		Selectable* currentHoveredGameObject;
		Selectable* lastHoveredGameObject;

		vector<Selectable*> raycastTargets = {};
	};
}


