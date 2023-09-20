#pragma once

#include "Renderer.h"

namespace RayEngine
{
	/// <summary>
	/// string text, float fontSize or string, Font, fontSize
	/// </summary>
	class TextRenderer final : public Renderer
	{
	public:	
		enum class CenterType
		{
			X,
			Y,
		};

		inline string_view GetText() const { return text; }
		constexpr inline Font GetFont() const { return font; }
		constexpr inline float GetFontSize() const { return fontSize; }
		constexpr inline float GetSpacing() const { return spacing; }
		inline void UseCenterPosition(bool center) { useCenterPosition = center; }

		void SetText(const string& text);
		void SetFont(Font font);
		void SetSpacing(float spacing);
		void CenterBetween(float min, float max, CenterType center = CenterType::X);
		

		RayEngine::Bounds Bounds() const override;
		void InternalDraw() const override;

		TextRenderer() : text(""), font(defaultFont), fontSize(15.f) { size = {}; }
		TextRenderer(RayEngine::GameObject* gameObject, string text, float fontSize = 15.f, Color color = WHITE);
		TextRenderer(RayEngine::GameObject* gameObject, string text, Font font, float fontSize = 15.f, Color color = WHITE);


		static TextRenderer* Create(string text, float fontSize = 15.f, Color color = WHITE, Font font = {}, float spacing = 1.f);
		inline static void SetDefaultFont(Font font) { defaultFont = font; }

		static Vector2 GetSize(const string& text, Font font, Vector2 scale, float fontSize, float spacing);
	private:
		string text;
		Vector2 size;
		Font font;
		float fontSize;
		float spacing = 1;
		bool useCenterPosition = true;

		inline static Font defaultFont = {};

		
#ifdef ENGINEDLL
	public:
#else
	private:
#endif
	   
		inline static void Shutdown()
		{
			UnloadFont(defaultFont);
		}
		
	};
}
