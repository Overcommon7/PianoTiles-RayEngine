#include "pch.h"
#include "DropdownOption.h"

#include "Button.h"
#include "TextRenderer.h"
#include "Collider.h"
#include "Bounds.h"

#include "GameObject.h"

void RayEngine::DropdownOption::SetActive(bool active)
{
	button->GameObject()->SetActive(active);
}

void RayEngine::DropdownOption::SetText(const string_view& data)
{
	text->SetText(data.data());
	text->Transform()->SetPosition(button->GetCollider()->Bounds().Center());	
}

RayEngine::Transform* RayEngine::DropdownOption::Transform()
{
	return button->Transform();
}

string_view RayEngine::DropdownOption::GetData() const
{
	return text->GetText();
}

RayEngine::DropdownOption::DropdownOption(Vector2 size, const string& data, Color BGColor, Color textColor)
{
	button = Button::Create(size, BGColor);
	text = TextRenderer::Create(data, size.y * 0.9f, textColor);
	text->Transform()->SetParent(button->Transform());
	text->Transform()->SetPosition(button->GetCollider()->Bounds().Center());
	isSelected = false;
}
