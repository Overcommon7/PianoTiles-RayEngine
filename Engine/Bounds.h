#pragma once

namespace RayEngine
{
	struct Bounds
	{
		Bounds(Vector2 position, Vector2 size, Vector2 scale);

		inline constexpr Vector2 Min() const { return position; }
		inline Vector2 const Max() const { return Vector2Add(position, Vector2Multiply(size, scale)); }
		inline Vector2 const Center() const { return Vector2Add(position, Vector2Scale(Vector2Multiply(size, scale), 0.5f)); }
		inline Vector2 const Size() const { return Vector2Multiply(size, scale); }

	private:

		Vector2 position;
		Vector2 size;
		Vector2 scale;
	};
}

