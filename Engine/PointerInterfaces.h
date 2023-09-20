#pragma once
#include "Interfaces.h"

namespace RayEngine
{
	class Collider;

	class IPointer : public IUpdate
	{
	public:
		bool IsHovered() const { return isHovered; }
		void SetCollider(Collider* collider);
		float TimeSpentHoveredInCollider() const { return timeInCollider; }
	protected:

		IPointer() : IUpdate(), collider(nullptr) {}
		IPointer(Collider* collider) : IUpdate(), collider(collider) {}

		virtual void Update() override;
		Collider* collider;
		bool isHovered = false;
		bool lastFrame = false;
		float timeInCollider = 0;

		virtual ~IPointer()
		{
			collider = nullptr;
		}
	};

	class IPointerEnterHandler : public IPointer
	{
	public:
		float TimeOfPointerEnter() const { return timeOfPointerEnter; }
		virtual void OnPointerEnter() = 0;
	protected:
		float timeOfPointerEnter = 0;
		virtual void Update() override;
		~IPointerEnterHandler() {}
	};

	class IPointerExitHandler : public IPointer
	{
	public:
		float TimeOfPointerExit() const { return timeOfPointerExit; }
		virtual void OnPointerExit() = 0;
	protected:
		float timeOfPointerExit = 0;
		virtual void Update() override;
		~IPointerExitHandler() {}
	};

	class IPointerUpHandler : public IPointer
	{
	public:
		float TimeOfPointerUp() const { return timeOfPointerUp; }
		virtual void OnPointerUp() = 0;
	protected:
		float timeOfPointerUp = 0;
		virtual void Update() override;
		~IPointerUpHandler() {}
	};

	class IPointerDownHandler : public IPointer
	{
	public:
		float TimeOfPointerDown() const { return timeOfPointerDown; }
		virtual void OnPointerDown() = 0;
	protected:
		float timeOfPointerDown = 0;
		virtual void Update() override;
		~IPointerDownHandler() {}
	};

	class IPointerClickHandler : public IPointer
	{
	public:
		float TimeOfPointerClick() const { return timeOfPointerClick; }
		virtual void OnPointerClick() = 0;

	protected:
		float timeOfPointerClick = 0;
		virtual void Update() override;
		~IPointerClickHandler() {}
	};
}

