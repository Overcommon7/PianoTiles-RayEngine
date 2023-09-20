#include "pch.h"
#include "Object.h"

RayEngine::Object::Object(const string& name) : name(name), isActive(true)
{
	id = Random<size_t>(ULLONG_MAX - 1);
}
