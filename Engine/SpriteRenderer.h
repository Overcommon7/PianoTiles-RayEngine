#pragma once
#include "Renderer.h"
#include "Structs.h"

namespace RayEngine
{
	struct Bounds;
	/// <summary>
	/// (string filename / Shape = Square), Vector2 size = { 10, 10 }, Color tint = WHITE, int sortingLayer = 0 
	/// </summary>
	class SpriteRenderer : public Renderer
	{
		Vector2 size;
		size_t hash;
		int index;
		Shape shape = Shape::Square;
		static inline vector<std::pair<size_t, Texture2D>> textures = {};

		static Texture2D GetTexture(size_t hash);
		static bool HasTexture(size_t hash);

	public:
		virtual void InternalDraw() const override;
		virtual RayEngine::Bounds Bounds() const override;



		static void Shutdown();
		Shape GetShape() const { return shape; }
		void SetShape(Shape shape) { if (hash == 0) this->shape = shape; }

		void SetTexture(size_t hash, bool resize = true);
		void SetTexture(string filepath, bool resize = true);
		void SetTexture(Image image, bool resize = true);
		void SetTexture(const Texture2D& texture, bool resize = true);

		static void DrawRectangle(Vector2 position, Vector2 size, float roatation, Color color);
		static void DrawCircle(const RayEngine::Bounds& bounds, Color color);
		static void DrawTriangle(const RayEngine::Bounds& bounds, float rotation, Color color);

		const Texture2D& GetTexture() { return GetTexture(hash); }
		bool HasTexture() { return HasTexture(hash); }
		inline const size_t GetHash() const { return hash; }

		SpriteRenderer() = default;
		SpriteRenderer(RayEngine::GameObject* gameObject, Shape shape = Shape::Square, Vector2 size = { 10, 10 }, Color tint = WHITE, int sortingLayer = 0);
		SpriteRenderer(RayEngine::GameObject* gameObject, string filename, Vector2 size = { -1, -1 }, Color tint = WHITE, int sortingLayer = 0);
	};
}



