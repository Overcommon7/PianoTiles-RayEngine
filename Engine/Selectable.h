#pragma once

#include "Component.h"
#include "Interfaces.h"
#include "Delegate.h"

namespace RayEngine
{
	class SpriteRenderer;
	class Collider;
	class GameObject;

	class Selectable : public Component, public IUpdate, public IObservable
	{
	public:
		Selectable() = default;
		Selectable(Collider* collider, const string& name = "Selectable");
		Selectable(RayEngine::GameObject* gameObject, const string& name = "Selectable");

		struct Colors
		{
			Color hoverColor = { 60, 60, 60, 165 };
			Color selectedColor = { 120, 120, 120, 165 };
			Color clickedColor = { 180, 180, 180, 165 };
			Color normalColor = BLANK;
		};

		inline constexpr bool IsRayCastTarget() const { return isRaycastTarget; }
		inline void SetRayCastTarget(bool target) { isRaycastTarget = target; }
		inline const bool IsSelcted() const { return isSelected; }
		inline const bool IsHovered() const { return isHovered; }
		inline void HighlightWhenSelected(bool highlight) { highlightWhenSelected = highlight; }
		inline bool AcceptsRightClicks() const { return acceptsRightClicks; }
		inline void CanAcceptRightClicks(bool accept) { acceptsRightClicks = accept; }


		Colors& GetColors() { return colors; }
		Color GetHighlightColor() const;

		inline const float TimeInCollider() const { return timeInCollider; }
		const Collider* const GetCollider() const { return collider; }

		virtual void OnPointerClick();

		 inline Delegate1<Selectable>& GetClickEvent() { return OnClick; }
		 inline Delegate1<Selectable>& GetEnterEvent() { return OnEnter; }
		 inline Delegate1<Selectable>& GetExitEvent() { return OnExit; }
		 inline Delegate1<Selectable>& GetDeselectEvent() { return OnDeselect; }

		 virtual ~Selectable();
#ifdef ENGINEDLL 
	public:
#else
	private:
#endif
		void SetSelected(bool selected);
		void SetHovered(bool selected);
		float timeInCollider = 0;

	protected:
		
		Delegate1<Selectable> OnClick;
		Delegate1<Selectable> OnEnter;
		Delegate1<Selectable> OnExit;
		Delegate1<Selectable> OnDeselect;

		virtual void OnInvoke();
		virtual void Update() override;

		Colors colors;
		Collider* collider;
		bool highlightWhenSelected = true;

	private:
		bool isRaycastTarget = true;
		bool isSelected = false;
		bool isHovered = false;
		bool acceptsRightClicks = false;
		float timeOfClick = 0;

		
		bool internalHover = false;

		inline static float const CLICK_TIME = 0.08f;

		
		virtual void OnPointerEnter();
		virtual void OnPointerExit();
		
	};
}



