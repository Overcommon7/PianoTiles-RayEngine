#pragma once

namespace RayEngine
{
	using ObjectID = size_t;
	class Object
	{
	public:
		inline void SetActive(bool active) { isActive = active; }
		inline bool IsActive() const { return isActive; }
		inline void SetName(const string& name) { this->name = name; }
		friend bool operator==(const Object& object1, const Object& object2) { return object1.id == object2.id; }


		const string_view Name() const { return name; }
		const ObjectID ID() const { return id; }

	protected:			  
		bool isActive;
		ObjectID id;
		string name;

		Object(const string& name);
		Object() = default;

	public:
		Object(const Object& obj) = delete;
		Object(const Object&& obj) = delete;
		Object& operator=(const Object& obj) = delete;
		Object& operator=(const Object&& obj) = delete;

		virtual ~Object() {}
	};
}
