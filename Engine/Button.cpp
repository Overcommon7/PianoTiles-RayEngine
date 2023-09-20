#include "pch.h"
#include "Button.h"

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"

#include "Bounds.h"
#include "Structs.h"

RayEngine::Button::Button(RayEngine::GameObject* gameObject, RayEngine::Collider* collider)
	: Selectable(collider)
{
	this->collider = collider;
	spriteRenderer = gameObject->AddComponent<SpriteRenderer>
		(collider->GetShape(), collider->Bounds().Size(), WHITE, 0);

	colors.selectedColor = BLANK;
	spriteRenderer->OnDraw() += this;
}

RayEngine::Button::Button(RayEngine::GameObject* gameObject, Vector2 size, Color color, RayEngine::Shape shape)
	: Selectable(gameObject)
{
	collider = gameObject->AddComponent<BoxCollider>(size);
	spriteRenderer = gameObject->AddComponent<SpriteRenderer>(shape, size, color, 0);

	
	colors.selectedColor = BLANK;
	spriteRenderer->OnDraw() += this;
}

RayEngine::Button::Button(RayEngine::GameObject* gameObject, const string& filepath, Vector2 size, Color color)
	: Selectable(gameObject)
{		
	spriteRenderer = gameObject->AddComponent<SpriteRenderer>(filepath, size, color, 0);
	collider = gameObject->AddComponent<BoxCollider>(spriteRenderer->Bounds().Size());

	colors.selectedColor = BLANK;
	spriteRenderer->OnDraw() += this;
}

RayEngine::Button* RayEngine::Button::Create(const string& filepath, Vector2 size, Color color)
{
	return GameObject::Create()->AddComponent<Button>(filepath, size, color);
}

RayEngine::Button* RayEngine::Button::Create(Vector2 size, Color color, RayEngine::Shape shape)
{
	return GameObject::Create()->AddComponent<Button>(size, color, shape);
}
