#pragma once

namespace RayEngine
{
	class System
	{
	public:

		static System* Get();

		void Run(const Base::Data& data,
			vector<function<void()>> initializers,
			vector<function<void()>> update,
			vector<function<void()>> draw,
			vector<function<void()>> shutdown);
	private:
		System() {}
	public:
		
		System(const System& s) = delete;
		System(const System&& s) = delete;
		System& operator=(const System& s) = delete;
		System& operator=(const System&& s) = delete;
	};
}



