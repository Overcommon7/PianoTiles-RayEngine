#include "pch.h"
#include "TextRenderer.h"

#include "Bounds.h"
#include "Transform.h"
#include "GameObject.h"

void RayEngine::TextRenderer::SetText(const string& text)
{
    this->text = text;
    size = GetSize(text, font, transform->Scale(), fontSize, spacing);
}

void RayEngine::TextRenderer::SetFont(Font font)
{
    this->font = font;
    size = GetSize(text, font, transform->Scale(), fontSize, spacing);
}

void RayEngine::TextRenderer::SetSpacing(float spacing)
{
    this->spacing = spacing; 
    size = GetSize(text, font, transform->Scale(), fontSize, spacing);
}

void RayEngine::TextRenderer::CenterBetween(float min, float max, CenterType center)
{
    if (center == CenterType::X)
        transform->SetXPosition((max - min) * 0.5f - (Bounds().Size().x * 0.5f));
    else if (center == CenterType::Y)
        transform->SetYPosition((max - min) * 0.5f - (Bounds().Size().y * 0.5f));
}

RayEngine::Bounds RayEngine::TextRenderer::Bounds() const
{
    return RayEngine::Bounds(transform->Position(), size, {1, 1});
}

void RayEngine::TextRenderer::InternalDraw() const
{
    auto scale = transform->Scale();

    auto finalScale = 1.f;
    if (scale.x != 1.f || scale.y != 1.f)
        finalScale = Vector2Length(scale);

    auto position = useCenterPosition ? Bounds().Center() : transform->Position();

    ::DrawTextPro(font, text.c_str(), position, {size.x * 0.5f, size.y * 0.5f}, transform->Rotation(), fontSize * finalScale, spacing, color);
}

RayEngine::TextRenderer::TextRenderer(RayEngine::GameObject* gameObject, string text, float fontSize, Color color)
    : Renderer(gameObject, 0, color, "TextRenderer"), font(defaultFont), text(text), fontSize(fontSize)
{
    size = GetSize(text, font, transform->Scale(), fontSize, spacing);
}

RayEngine::TextRenderer::TextRenderer(RayEngine::GameObject* gameObject, string text, Font font, float fontSize, Color color)
    : Renderer(gameObject, 0, color, "TextRenderer"), text(text), fontSize(fontSize)
{
    if (defaultFont.texture.id == 0)
        defaultFont = GetFontDefault();

    if (font.texture.id == 0)
        this->font = defaultFont;
    else this->font = font;

    size = GetSize(text, font, transform->Scale(), fontSize, spacing);
}

RayEngine::TextRenderer* RayEngine::TextRenderer::Create(string text, float fontSize, Color color, Font font, float spacing)
{
    auto obj = GameObject::Create();
    if (font.texture.id == 0)
        font = defaultFont;

    auto value = obj->AddComponent<TextRenderer>(text, font, fontSize, color);
    if (spacing != 1.f) value->SetSpacing(spacing);
    return value;
}

Vector2 RayEngine::TextRenderer::GetSize(const string& text, Font font, Vector2 scale, float fontSize, float spacing)
{
    auto finalScale = 1.f;
    if (scale.x != 1.f || scale.y != 1.f)
        finalScale = Vector2Length(scale);

    return MeasureTextEx(font, text.c_str(), fontSize * finalScale, spacing);
}
