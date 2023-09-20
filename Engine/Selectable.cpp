#include "pch.h"
#include "Selectable.h"

#include "Collider.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

#include "Bounds.h"
#include "EventSystem.h"


RayEngine::Selectable::Selectable(Collider* collider, const string& name)
	: Component(collider->GameObject(), name), collider(collider)
{

}

RayEngine::Selectable::Selectable(RayEngine::GameObject* gameObject, const string& name)
	: Component(gameObject, name)
{
	collider = nullptr;
}

RayEngine::Selectable::~Selectable()
{
	if (isSelected)
		EventSystem::Get().Select(nullptr);
	if (isHovered)
		EventSystem::Get().Hover(nullptr);
}

void RayEngine::Selectable::SetSelected(bool selected)
{
	if (selected)
		OnPointerClick();

	if (selected == isSelected) return;

	isSelected = selected;
	if (!isSelected)
		OnDeselect.Invoke(*this);
}

void RayEngine::Selectable::SetHovered(bool selected)
{
	if (!selected)
		OnPointerExit();
	else
		OnPointerEnter();
}

Color RayEngine::Selectable::GetHighlightColor() const
{
	if (isHovered)
	{
		if (Time::Now() - timeOfClick < CLICK_TIME) return colors.clickedColor;
		if (highlightWhenSelected || !isSelected) return colors.hoverColor;
		return BLANK;	
	}

	if (isSelected) return colors.selectedColor;
	return colors.normalColor;
}

void RayEngine::Selectable::OnInvoke()
{
	if (!collider) return;

	Color color = GetHighlightColor();
	if (color.a == 0) return;

	switch (collider->GetShape())
	{
	case RayEngine::Shape::Square:
		RayEngine::SpriteRenderer::DrawRectangle(
			transform->Position(), collider->Bounds().Size(), 
			transform->Rotation(), color);
		break;
	case RayEngine::Shape::Circle:
		RayEngine::SpriteRenderer::DrawCircle(collider->Bounds(), color);
		break;
	case RayEngine::Shape::Triangle:
		RayEngine::SpriteRenderer::DrawTriangle(collider->Bounds(), transform->Rotation(), color);
		break;
	}
	
}

void RayEngine::Selectable::Update()
{
	if (!collider) return;

	internalHover = collider->IsColliding(Mouse::Position());

	if (internalHover)
	{
		EventSystem::Get().Hover(this);
	}
}

void RayEngine::Selectable::OnPointerClick()
{
	timeOfClick = Time::Now();
	OnClick.Invoke(*this);
}

void RayEngine::Selectable::OnPointerEnter()
{
	OnEnter.Invoke(*this);
	isHovered = true;
}

void RayEngine::Selectable::OnPointerExit()
{
	timeInCollider = 0;
	isHovered = false;
	OnExit.Invoke(*this);
}
