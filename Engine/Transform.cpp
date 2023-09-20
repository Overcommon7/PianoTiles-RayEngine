#include "pch.h"
#include "Transform.h"

#include "GameObject.h"

RayEngine::Transform::Transform(RayEngine::GameObject* gameObject, Vector2 position)
	: Component(gameObject, "Transform"), position(position), rotation(0.0f), scale({1, 1})
{

}

void RayEngine::Transform::SetPosition(Vector2 position)
{
	auto delta = this->position;
	this->position = position;
	delta = Vector2Subtract(position, delta);

	for (auto child : children)
		child->Translate(delta);
}

void RayEngine::Transform::SetLocalPosition(Vector2 position)
{
	if (parent != nullptr)
		SetPosition(Vector2Add(parent->position, position));
	else SetPosition(position);
}

void RayEngine::Transform::SetScale(Vector2 scale)
{
	auto delta = this->scale;
	this->scale = scale;
	delta = Vector2Subtract(scale, delta);

	for (auto child : children)
		child->OffsetScale(delta);
}

void RayEngine::Transform::SetLocalScale(Vector2 scale)
{
	if (parent != nullptr)
		SetScale(Vector2Multiply(parent->scale, scale));
	else SetScale(scale);
}

void RayEngine::Transform::SetRotation(float rotation)
{
	float delta = this->rotation;
	this->rotation = rotation;
	rotation -= delta;

	for (auto child : children)
		child->Rotate(delta);
}

void RayEngine::Transform::SetLocalRotation(float rotation)
{
	if (parent != nullptr)
		SetRotation(rotation + parent->rotation);
	else SetRotation(rotation);
}

void RayEngine::Transform::Translate(Vector2 delta)
{
	position = Vector2Add(position, delta);

	for (auto child : children)
		child->Translate(delta);
}

void RayEngine::Transform::OffsetScale(Vector2 delta)
{
	scale = Vector2Add(scale, delta);
	
	for (auto child : children)
		child->OffsetScale(delta);
}

void RayEngine::Transform::Rotate(float delta)
{
	rotation += delta;

	for (auto child : children)
		child->Rotate(delta);
}

void RayEngine::Transform::TranslateXPos(float delta)
{
	Translate({delta, 0});
}

void RayEngine::Transform::TranslateYPos(float delta)
{
	Translate({ 0, delta });
}

void RayEngine::Transform::OffsetXScale(float delta)
{
	OffsetScale({ delta, 0 });
}

void RayEngine::Transform::OffsetYScale(float delta)
{
	OffsetScale({ 0, delta });
}

constexpr float RayEngine::Transform::LocalRotation() const
{
	if (parent != nullptr) return rotation - parent->rotation;
	return rotation;
}

constexpr Vector2 RayEngine::Transform::LocalPosition() const
{
	if (parent != nullptr) return Vector2Subtract(position, parent->position);
	return position;
}

constexpr Vector2 RayEngine::Transform::LocalScale() const
{
	if (parent != nullptr) return Vector2Subtract(scale, parent->scale);
	return scale;
}

RayEngine::Transform* RayEngine::Transform::Root()
{
	RayEngine::Transform* parent = this->parent;
	while (parent && parent->parent)
		parent = parent->parent;
	return parent;
}

void RayEngine::Transform::SetParent(Transform* transform, bool maintianWorldPosition)
{
	if (parent == transform) return;
	if (parent)
	{
		parent->children.erase(find(parent->children.begin(), parent->children.end(), this));
	}
	
	parent = transform;
	
	if (!parent) return;
	parent->children.push_back(this);
	if (!maintianWorldPosition)
	{
		auto local = LocalPosition();
		SetLocalPosition(local);
	}
}
