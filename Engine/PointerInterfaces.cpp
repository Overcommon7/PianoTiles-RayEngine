#include "pch.h"
#include "PointerInterfaces.h"

#include "Collider.h"


void RayEngine::IPointerEnterHandler::Update()
{
	IPointer::Update();
	if (isHovered && !lastFrame)
	{
		OnPointerEnter();
		timeOfPointerEnter = Time::Now();
	}
		

	lastFrame = isHovered;
}

void RayEngine::IPointerExitHandler::Update()
{
	IPointer::Update();
	if (!isHovered && lastFrame)
	{
		OnPointerExit();
		timeOfPointerExit = Time::Now();
	}
		

	lastFrame = isHovered;
}

void RayEngine::IPointerUpHandler::Update()
{
	IPointer::Update();
	if (!isHovered)	return;

	if (lastFrame && !Mouse::IsLeftDown())
	{
		OnPointerUp();
		timeOfPointerUp = Time::Now();
	}
		

	lastFrame = Mouse::IsLeftDown();
}

void RayEngine::IPointerDownHandler::Update()
{
	IPointer::Update();
	if (!isHovered)	return;

	if (!lastFrame && Mouse::IsLeftDown())
	{
		OnPointerDown();
		timeOfPointerDown = Time::Now();
	}
		

	lastFrame = Mouse::IsLeftDown();
}

void RayEngine::IPointerClickHandler::Update()
{
	if (!isHovered) return;

	if (Mouse::IsLeftClicked())
	{
		OnPointerClick();
		timeOfPointerClick = Time::Now();
	}
		
}

void RayEngine::IPointer::SetCollider(Collider* collider)
{
	this->collider = collider;
}

void RayEngine::IPointer::Update()
{
	if (!collider)
	{
		return;
	}

	isHovered = collider->IsColliding(Mouse::Position());
	if (!isHovered) timeInCollider = 0;
	else timeInCollider += Time::DeltaTime();
}
