#pragma once

namespace RayEngine
{
	class Button;
	class TextRenderer;
	class Transform;

	class DropdownOption
	{
		Button* button = nullptr;
		TextRenderer* text = nullptr;

		bool isSelected = false;

	public:

		inline bool IsSelected() const { return isSelected; }
		inline void SetSelected(bool selected) { isSelected = selected; }
		inline Button* const Button() { return button; }
		inline TextRenderer* const Text() { return text; }

		string_view GetData() const;
		void SetActive(bool active);
		void SetText(const string_view& data);
		RayEngine::Transform* Transform();

		DropdownOption(Vector2 size, const string& data, Color BGColor, Color textColor);
		DropdownOption() = default;
	};
}
