#pragma once

namespace RayEngine
{
	class Time
	{
	public:
		inline static const float Now() { return now; }
		inline static const float DeltaTime() { return dt; }

		static void Update();
	private:
		static inline float now = 0;
		static inline float dt = 0;
	};
}
