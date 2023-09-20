#include "pch.h"
#include "Dropdown.h"

#include "GameObject.h"
#include "Button.h"
#include "BoxCollider.h"
#include "Bounds.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"

RayEngine::Dropdown::Dropdown(RayEngine::GameObject* gameObject, const vector<string>& data, Vector2 dropdownSize, int viewableOptions, Color textColor, Color BGColor)
	: Component(gameObject, "Dropdown"), textColor(textColor), BGColor(BGColor), size(dropdownSize), viewableOptions(viewableOptions)
{
	if (data.empty())
		throw std::exception("Data Was Empty");

	selectedOption = DropdownOption(dropdownSize, data.front(), BGColor, textColor);
	selectedOption.Transform()->SetPosition(transform->Position());
	selectedOption.Transform()->SetParent(transform);
	selectedOption.Button()->GetClickEvent() += this;
	selectedOption.SetSelected(true);

	scrollArea = gameObject->AddComponent<BoxCollider>(Vector2(size.x, size.y * (viewableOptions + 1)));
	yPostion = transform->Position().y + size.y;

	options.reserve(data.size());
	AddOptions(data);
	options.front().SetSelected(0);

	selectedOption.Button()->GetDeselectEvent() += &onDeselect;
	ChangeState(State::Collapsed);
}

RayEngine::Dropdown* RayEngine::Dropdown::Create(const vector<string>& data, Vector2 dropdownSize, int viewableOptions, Color textColor, Color BGColor)
{
	return GameObject::Create()->AddComponent<Dropdown>(data, dropdownSize, viewableOptions, textColor, BGColor);
}

void RayEngine::Dropdown::AddOption(const string& data)
{
	AddOptionInternal(data);
	SetViewableOptions();
}

void RayEngine::Dropdown::AddOptions(const vector<string>& data)
{
	for (const auto& str : data)
		AddOptionInternal(str);
	SetViewableOptions();
}

void RayEngine::Dropdown::AddOptionInternal(const string& data)
{
	auto& option = options.emplace_back(DropdownOption(size, data, BGColor, textColor));
	option.Transform()->SetPosition({ transform->Position().x, yPostion });
	yPostion = option.Button()->GetCollider()->Bounds().Max().y;
	option.Transform()->SetParent(transform);
	option.Button()->GetClickEvent() += this;
}

void RayEngine::Dropdown::ChangeState(State state)
{
	this->state = state;
	if (state == State::Expanded)
	{
		SetViewableOptions();
	}
	else
	{
		for (auto& option : options)
			option.SetActive(false);
	}
}

void RayEngine::Dropdown::SetSelectedOption(const string& data, bool notifyListeners)
{
	for (auto& option : options)
	{
		if (option.GetData() != data) continue;

		selectedOption.SetText(option.GetData());
		option.SetSelected(true);

		if (notifyListeners)
		{
			string data = option.GetData().data();
			onValueSelected.Invoke(data);
		}
			
		return;
	}
}

void RayEngine::Dropdown::SetSortingLayer(int layer)
{
	selectedOption.Button()->Renderer()->SetSortingLayer(layer);
	selectedOption.Text()->SetSortingLayer(layer);

	for (auto option : options)
	{
		option.Button()->Renderer()->SetSortingLayer(layer);
		option.Text()->SetSortingLayer(layer);
	}
}

void RayEngine::Dropdown::Update()
{
	if (state == State::Collapsed) return;
	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::None) return;
	if (options.empty()) return;

	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Up &&
		options.back().Button()->GetCollider()->Bounds().Max().y <= scrollArea->Bounds().Max().y) return;
	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Down &&
		options.front().Button()->GetCollider()->Bounds().Min().y >= selectedOption.Button()->GetCollider()->Bounds().Max().y) return;
		

	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Up)
		++startIndex;
	else --startIndex;

	startIndex = std::clamp(startIndex, 0, (int)options.size() - viewableOptions);
	SetViewableOptions();
}

void RayEngine::Dropdown::OnInvoke(Selectable& arg1)
{
	if (arg1 == *selectedOption.Button())
	{
		ChangeState((State)(!(bool)state));
		return;
	}

	for (auto& option : options)
	{
		if (*option.Button() != arg1) continue;

		selectedOption.SetText(option.GetData());
		option.SetSelected(true);
		return;
	}
}

void RayEngine::Dropdown::SetViewableOptions()
{
	if (state == State::Collapsed) return;

	const auto size = options.size();


	float yMove = 0;
	if (Mouse::Wheel::Vertical() != Mouse::Wheel::Movement::None)
	{
		yMove = Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Up
			? -this->size.y : this->size.y;
	}

	for (int i = 0; i < startIndex; i++)
	{
		if (yMove != 0)
			options[i].Transform()->TranslateYPos(yMove);
		options[i].SetActive(false);
	}
	for (int i = startIndex; i < startIndex + viewableOptions && i < size; i++)
	{
		if (yMove != 0)
			options[i].Transform()->TranslateYPos(yMove);
		options[i].SetActive(true);
	}
	for (int i = startIndex + viewableOptions; i < size; i++)
	{
		if (yMove != 0)
			options[i].Transform()->TranslateYPos(yMove);
		options[i].SetActive(false);
	}
}

void RayEngine::Dropdown::DropDownDeselect::OnInvoke(Selectable& arg1)
{
	arg1.Transform()->Parent()->GameObject()->GetComponent<Dropdown>()->ChangeState(State::Collapsed);
}
