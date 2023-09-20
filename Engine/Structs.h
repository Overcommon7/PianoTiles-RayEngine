#pragma once

namespace RayEngine
{
	enum class Shape
	{
		Square,
		Circle,
		Triangle,
	};

	struct Triangle
	{
		union
		{
			struct
			{
				Vector2 vertice_1;
				Vector2 vertice_2;
				Vector2 vertice_3;
			};
			std::array<Vector2, 3> verticies;
		};
	};
}
