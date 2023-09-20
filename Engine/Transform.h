#pragma once
#include "Component.h"

namespace RayEngine
{
	/// <summary>
	/// Vector2 position = {0, 0}
	/// </summary>
	class Transform : public Component
	{
	public:
		Transform(RayEngine::GameObject* gameObject, Vector2 position = {});

		void SetPosition(Vector2 position);
		void SetLocalPosition(Vector2 position);
		void SetScale(Vector2 position);
		void SetLocalScale(Vector2 position);
		void SetRotation(float rotation);
		void SetLocalRotation(float rotation);

		void Translate(Vector2 delta);
		void OffsetScale(Vector2 delta);
		void Rotate(float delta);

		void TranslateXPos(float delta);
		void TranslateYPos(float delta);
		void OffsetXScale(float delta);
		void OffsetYScale(float delta);

		inline constexpr Vector2 Position() const { return position; }
		inline constexpr Vector2 Scale() const { return scale; }
		inline constexpr float Rotation() const { return rotation; }

		inline void SetXPosition(float x) { SetPosition({ x, position.y }); }
		inline void SetYPosition(float y) { SetPosition({ position.x, y }); }

		inline void SetScaleX(float x) { SetScale({ x, scale.y }); }
		inline void SetScaleY(float y) { SetScale({ scale.x, y }); }

		constexpr float LocalRotation() const;
		constexpr Vector2 LocalPosition() const;
		constexpr Vector2 LocalScale() const;

		Transform* Root();
		Transform* GetChild(int index) const { return children[index]; }
		int ChildCount() const { return (int)children.size(); }
		void SetParent(Transform* transform, bool maintianWorldPosition = true);
		constexpr inline const Transform* const Parent() const { return parent; }
		
	private:
		Vector2 position;
		Vector2 scale;
		float rotation;

		vector<Transform*> children = {};
		Transform* parent = nullptr;
	};
}


