#pragma once
#include "Selectable.h"

namespace RayEngine
{
	class TextRenderer;
	class Button;
	class GameObject;

	class InputField : public Component, public IUpdate, public IObservable
	{
	public:
		void SetText(const string& text);
		string_view GetText();
		void SetFont(Font font);
		void SetSpacing(float spacing);
		void SetOnlyNumbers(bool onlyNums);
		bool IsOnlyNumbersEnabled() const { return onlyNumbers; }
		inline Delegate1<string>& GetOnSubmit() { return onSubmit; }

		void SetSortingLayer(int layer);

		InputField() = default;
		InputField(RayEngine::GameObject* gameObject, Vector2 BGSize, float fontSize, Color normalColor, Color BGColor, const string& emptyText, Color emptyTextColor, Font font);

		static InputField* Create(Vector2 BGSize, float fontSize = 15.f, Color normalColor = BLACK, Color BGColor = WHITE, const string& emptyText = "Enter Text...", Color emptyTextColor = LIGHTGRAY, Font font = {});
	private:
		TextRenderer* textRenderer;
		Button* background;
		string emptyText;
		Color emptyTextColor;
		Color normalColor;
		Vector2 cursorPosition;
		Delegate1<string> onSubmit;

		bool drawCursor = true;
		bool isEmpty = true;
		int cursorIndex = 0;
		float cursorTimer = 0;
		bool onlyNumbers = false;

		


		const static inline float CURSOR_TIME = 0.75f;

		constexpr inline int Index() const { return cursorIndex - 1; }
		void OnInvoke() override;
		void UpdateCursor();
		void OnKeyPressed(string& text);
		void OnCharPressed(string& text);
		void SetCursorPosition(const string& text);

#ifdef ENGINEDLL
	public:
#else
	private:
#endif // ENGINEDLL

		void Update() override;
	};
}
