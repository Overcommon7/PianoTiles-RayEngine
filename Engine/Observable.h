#pragma once

namespace RayEngine
{
	class IObservable
	{
	public:
		virtual void OnInvoke() = 0;
	};

	template<class T>
	class IObservable1
	{
	public:
		virtual void OnInvoke(T& arg1) = 0;
	};

	template<class T1, class T2>
	class IObservable2
	{
	public:
		virtual void OnInvoke(T1& arg1, T2& arg2) = 0;
	};

	template<class T1, class T2, class T3>
	class IObservable3
	{
	public:
		virtual void OnInvoke(T1& arg1, T2& arg2, T3& arg3) = 0;
	};
}



