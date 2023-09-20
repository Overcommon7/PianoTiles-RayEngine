#pragma once
#include "Collider.h"
namespace RayEngine
{
	class GameObject;

	/// <summary>
	/// Vector2 size
	/// </summary>
	class BoxCollider : public Collider
	{
	public:
		
		BoxCollider() = default;
		BoxCollider(RayEngine::GameObject* gameObject, Vector2 size);

		Rectangle GetCollider() const;
		virtual bool IsColliding(Vector2 point) const override;
		virtual bool IsColliding(Circle circle) const override;
		virtual bool IsColliding(Rectangle rectangle) const override;
		virtual bool IsColliding(const BoxCollider& collider) const override;
	};	
}


