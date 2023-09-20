#pragma once
#include "Component.h"
#include "DropdownOption.h"
#include "Interfaces.h"
#include "Delegate.h"

namespace RayEngine
{
	class GameObject;
	class BoxCollider;
	class Selectable;

	

	class Dropdown : public Component, public IUpdate, public IObservable1<Selectable>
	{
	public:
		enum class State;
		Dropdown() = default;
		Dropdown(RayEngine::GameObject* gameObject, const vector<string>& data, Vector2 dropdownSize, int viewableOptions, Color textColor, Color BGColor);
		static Dropdown* Create(const vector<string>& data, Vector2 dropdownSize = {32, 16}, int viewableOptions = 5, Color textColor = BLACK, Color BGColor = LIGHTGRAY);

		void AddOption(const string& data);
		void AddOptions(const vector<string>& data);

		void SetSelectedOption(const string& data, bool notifyListeners = true);
		const string_view GetSelectedOptionData() const { return selectedOption.GetData(); }
		Delegate1<string>& GetOnValueChangedEvent() { return onValueSelected; }

		void SetSortingLayer(int layer);
	private:

		Delegate1<string> onValueSelected;
		vector<DropdownOption> options;
		DropdownOption selectedOption;

		State state = State::Expanded;
		Vector2 size;
		Color textColor;
		Color BGColor;
		BoxCollider* scrollArea;
		float yPostion;
		int viewableOptions;
		int startIndex = 0;

		void Update() override;
		void OnInvoke(Selectable& arg1) override;

		void SetViewableOptions();
		void AddOptionInternal(const string& data);
		void ChangeState(State state);

		class DropDownDeselect : public IObservable1<Selectable>
		{
			void OnInvoke(Selectable& arg1) override;
		};

		DropDownDeselect onDeselect;

	public:
		enum class State
		{
			Expanded = 0,
			Collapsed = 1
		};
	};
}
