#pragma once
#include "Component.h"
#include "Structs.h"
#include "Delegate.h"
#include "Interfaces.h"

namespace RayEngine
{
	class Button;
	class SpriteRenderer;
	class GameObject;
	class BoxCollider;

	/// <summary>
	/// Vector2 slidingArea, Vector2 handleSize, float max
	/// </summary>
	class Slider : public Component, public IUpdate
	{
		Button* handle;
		SpriteRenderer* fillAreaRenderer;
		BoxCollider* fillArea;

		Delegate1<float> onValueChanged;
		Delegate1<float> onRelease;

		float max;
		float value;
		float fraction;
		bool isSliding;
#ifdef ENGINEDLL
	public:
#else
	private:
#endif
		virtual void Update() override;

	public:
		Slider() = default;
		Slider(RayEngine::GameObject* gameObject, Vector2 slidingArea = { 200, 5 }, Vector2 handleSize = { 10, 35 }, float max = 1);

		void SetHandleColor(Color color);
		void SetFillAreaColor(Color color);

		void SetValue(float value);
		void SetMaxValue(float value);

		float GetValue() const { return value; }
		float GetMaxValue() const { return max; }

		Delegate1<float>& OnValueChanged() { return onValueChanged; }
		Delegate1<float>& OnRelease() { return onRelease; }

		static Slider* Create(Vector2 slidingArea = { 200, 5 }, Vector2 handleSize = { 10, 35 }, float max = 1);
	};
}



