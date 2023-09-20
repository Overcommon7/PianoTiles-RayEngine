#pragma once
#include "Object.h"

namespace RayEngine
{
	class GameObject;
	class Transform;

	class Component : public Object
	{
	public:

		void Destroy();
		inline RayEngine::Transform* Transform() const { return transform; }
		inline GameObject* GameObject() const { return gameObject; }

	protected:
		RayEngine::GameObject* gameObject;
		RayEngine::Transform* transform;

		Component(RayEngine::GameObject* gameObject, const string& name);
		Component() = default;

	public:
		Component(const Component& component) = delete;
		Component(const Component&& c) = delete;
		Component& operator=(const Component& c) = delete;
		Component& operator=(const Component&& c) = delete;

		virtual ~Component()
		{
			gameObject = nullptr;
			transform = nullptr;
		}
	};
}


