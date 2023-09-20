#include "pch.h"
#include "InputField.h"

#include "TextRenderer.h"
#include "GameObject.h"

#include "Button.h"
#include "SpriteRenderer.h"
#include "Bounds.h"
#include "Collider.h"

void RayEngine::InputField::SetText(const string& text)
{
	textRenderer->SetText(text);
	isEmpty = text.empty();

	if (isEmpty)
	{
		textRenderer->SetText("   " + emptyText);
		textRenderer->SetColor(emptyTextColor);
	}
	else
	{
		textRenderer->SetText(text);
		textRenderer->SetColor(normalColor);
	}

	SetCursorPosition(text);
}

string_view RayEngine::InputField::GetText()
{
	return textRenderer->GetText();
}

void RayEngine::InputField::SetFont(Font font)
{
	textRenderer->SetFont(font);
	SetCursorPosition(textRenderer->GetText().data());
}

void RayEngine::InputField::SetSpacing(float spacing)
{
	textRenderer->SetSpacing(spacing);
	SetCursorPosition(textRenderer->GetText().data());
}

void RayEngine::InputField::SetOnlyNumbers(bool onlyNums)
{
	onlyNumbers = onlyNums;

	if (isEmpty || !onlyNumbers) return;

	string text = textRenderer->GetText().data();
	text.erase(remove_if(text.begin(), text.end(), [](const char& c) {
		return !isdigit(c);
		}), text.end());

	cursorIndex = 0;
	SetText(text);
}

void RayEngine::InputField::SetSortingLayer(int layer)
{
	background->Renderer()->SetSortingLayer(layer);
	textRenderer->SetSortingLayer(layer);
}

RayEngine::InputField::InputField(RayEngine::GameObject* gameObject, Vector2 BGSize, float fontSize, Color normalColor, Color BGColor, const string& emptyText, Color emptyTextColor, Font font)
	: Component(gameObject, "InputField"), normalColor(normalColor), emptyText(emptyText), emptyTextColor(emptyTextColor), drawCursor(true), cursorIndex(0), cursorPosition({})
{
	background = Button::Create(BGSize, BGColor, Shape::Square);
	background->Transform()->SetParent(gameObject->Transform(), false);

	textRenderer = TextRenderer::Create("", fontSize, emptyTextColor, font);
	textRenderer->SetActive(false);

	textRenderer->Transform()->SetParent(background->Transform(), false);
	background->HighlightWhenSelected(false);
	background->Renderer()->OnDraw() += this;
	

	SetText("");
}

RayEngine::InputField* RayEngine::InputField::Create(Vector2 BGSize, float fontSize, Color normalColor, Color BGColor, const string& emptyText, Color emptyTextColor, Font font)
{
	return GameObject::Create()->AddComponent<InputField>(BGSize, fontSize, normalColor, BGColor, emptyText, emptyTextColor, font);
}

void RayEngine::InputField::OnInvoke()
{
	textRenderer->InternalDraw();
	if (!background->IsSelcted() || !drawCursor) return;

	auto size = background->Renderer()->Bounds().Size();
	SpriteRenderer::DrawRectangle(cursorPosition, { 1, textRenderer->GetFontSize() }, transform->Rotation(), normalColor);
}

void RayEngine::InputField::UpdateCursor()
{
	cursorTimer += Time::DeltaTime();
	if ((drawCursor && cursorTimer > CURSOR_TIME) ||
		(!drawCursor && cursorTimer > CURSOR_TIME * 0.85f))
	{
		drawCursor = !drawCursor;
		cursorTimer = 0;
	}
}

void RayEngine::InputField::OnKeyPressed(string& text)
{
	if (isEmpty) return;


	auto key = Keyboard::GetKeyPressedOrRepeating();

	if (key == KeyboardKey::KEY_ENTER || key == KeyboardKey::KEY_KP_ENTER)
	{
		onSubmit.Invoke(text);
		return;
	}

	if (key == KeyboardKey::KEY_BACKSPACE)
	{
		auto it = text.erase(text.begin() + Index());
		cursorIndex = (int)(it - text.begin());
		SetText(text);
	}
	else if (key == KeyboardKey::KEY_LEFT ||
			 key == KeyboardKey::KEY_RIGHT)
	{
		if (key == KeyboardKey::KEY_LEFT && cursorIndex > 0)
			--cursorIndex;
		else if (key == KeyboardKey::KEY_RIGHT && cursorIndex < text.length())
			++cursorIndex;
		else return;

		SetCursorPosition(text);
	}
}

void RayEngine::InputField::OnCharPressed(string& text)
{
	char character = Keyboard::GetCharPressedOrRepeating();
	if (onlyNumbers && !isdigit(character)) return;

	text.insert(text.begin() + cursorIndex, character);
	++cursorIndex;
	SetText(text);
}

void RayEngine::InputField::SetCursorPosition(const string& text)
{
	auto textBounds = textRenderer->Bounds();
	auto backgroundBounds = background->GetCollider()->Bounds();

	float size = MeasureTextEx(textRenderer->GetFont(), text.substr(0, cursorIndex).c_str(), textRenderer->GetFontSize(), textRenderer->GetSpacing()).x;

	cursorPosition.x = backgroundBounds.Min().x + size + 1;
	cursorPosition.y = textBounds.Min().y - (textBounds.Size().y * 0.5f);
}

void RayEngine::InputField::Update()
{  
	if (!background->IsSelcted()) return;
	UpdateCursor();
	if (!Keyboard::IsValidKeyPressedOrRepeating()) return;
	
	string text = isEmpty ? "" : textRenderer->GetText().data();

	if (Keyboard::IsValidCharPressedOrRepeating())
		OnCharPressed(text);
	else OnKeyPressed(text);
		

}
