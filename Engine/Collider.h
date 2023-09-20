#pragma once
#include "Component.h"
#include "Interfaces.h"
#include "Structs.h"

namespace RayEngine
{
	class BoxCollider;
	class GameObject;
	struct Bounds;

	class Collider : public	Component
	{
	protected:
		const Shape shape;
		Vector2 size;
		
		Collider() : Component(), shape(Shape::Square), size({}) {}
		Collider(RayEngine::GameObject* gameObject, const string& name, Vector2 size, Shape shape) : Component(gameObject, name), size(size), shape(shape) {}
	public:
		virtual bool IsColliding(Vector2 point) const = 0;
		virtual bool IsColliding(Circle circle) const = 0;
		virtual bool IsColliding(Rectangle rectangle) const = 0;
		virtual bool IsColliding(const BoxCollider& collider) const = 0;
		const constexpr Shape GetShape() const { return shape; }
		Bounds Bounds() const;
		inline virtual void SetSize(Vector2 size) { this->size = size; }

		virtual ~Collider() {}
	};
}


