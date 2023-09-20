#include "pch.h"
#include "Component.h"

#include "GameObject.h"
#include "Object.h"

void RayEngine::Component::Destroy()
{
	gameObject->Destroy(this);
}

RayEngine::Component::Component(RayEngine::GameObject* gameObject, const string& name) : Object(name)
{
	this->gameObject = gameObject;
	transform = gameObject->Transform();
}
