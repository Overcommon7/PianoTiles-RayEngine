#pragma once

#include "Selectable.h"
#include "Structs.h"

namespace RayEngine
{
	class GameObject;
	class Collider;
	class SpriteRenderer;

	/// <summary>
	/// Collider* or Vector2 size Color, Shape
	/// </summary>
	class Button : public Selectable
	{
	protected:
		SpriteRenderer* spriteRenderer;	 
	public:

		static Button* Create(const string& filepath, Vector2 size = { -1, -1 }, Color color = WHITE);
		static Button* Create(Vector2 size = {50, 50}, Color color = RED, RayEngine::Shape shape = RayEngine::Shape::Square);
		SpriteRenderer* const Renderer() const { return spriteRenderer; }

		Button() = default;
		Button(RayEngine::GameObject* gameObject, RayEngine::Collider* collider);
		Button(RayEngine::GameObject* gameObject, Vector2 size, Color color, RayEngine::Shape shape);
		Button(RayEngine::GameObject* gameObject, const string& filepath, Vector2 size, Color color);
	};
}



