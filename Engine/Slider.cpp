#include "pch.h"
#include "Slider.h"

#include "GameObject.h"
#include "Button.h"

#include "BoxCollider.h"
#include "SpriteRenderer.h"

#include "Bounds.h"

void RayEngine::Slider::Update()
{
    if (!Mouse::IsLeftDown())
    {
        if (isSliding)
            onRelease.Invoke(value);
        isSliding = false;
        return;
    }


    if (Mouse::IsLeftClicked() && handle->IsHovered()) isSliding = true;
    float temp = value;
    if (isSliding || (Mouse::IsLeftDoubleClicked() && fillArea->IsColliding(Mouse::Collider())))
    {
        auto bounds = fillArea->Bounds();

        handle->Transform()->SetXPosition(std::clamp(Mouse::Position().x, transform->Position().x, bounds.Max().x));
        fraction = (handle->Transform()->LocalPosition().x / bounds.Size().x);
        value = max * fraction;
    }
   

    if (value != temp)
        onValueChanged.Invoke(value);
}

void RayEngine::Slider::SetHandleColor(Color color)
{
    handle->Renderer()->SetColor(color);
}

void RayEngine::Slider::SetFillAreaColor(Color color)
{
    fillAreaRenderer->SetColor(color);
}

void RayEngine::Slider::SetValue(float value)
{
    if (value > max) this->value = max;
    this->value = value;

    fraction = value / max;
    handle->Transform()->SetXPosition(fillArea->Transform()->Position().x + (fillArea->Bounds().Size().x * fraction));
}

void RayEngine::Slider::SetMaxValue(float value)
{
    this->max = max;
    if (value > max)
    {
        value = max;
        fraction = 1;
    }
    else fraction = value / max;

    handle->Transform()->SetXPosition(fillArea->Transform()->Position().x + (fillArea->Bounds().Size().x * fraction));
}

RayEngine::Slider* RayEngine::Slider::Create(Vector2 fillArea, Vector2 handleSize, float max)
{
    auto obj = GameObject::Create();
    return obj->AddComponent<Slider>(fillArea, handleSize, max);
}

RayEngine::Slider::Slider(RayEngine::GameObject* gameObject, Vector2 fillArea, Vector2 handleSize, float max)
    : Component(gameObject, "Slider"), fraction(0), max(max), isSliding(false)
{
    this->fillArea = gameObject->AddComponent<BoxCollider>(fillArea);
    fillAreaRenderer = gameObject->AddComponent<SpriteRenderer>(Shape::Square, fillArea);

    handle = Button::Create(handleSize, GRAY, Shape::Square);
    handle->Transform()->SetParent(gameObject->Transform(), false);
    handle->Transform()->SetLocalPosition({ 0, (handle->GetCollider()->Bounds().Size().y * -0.5f) + (fillArea.y * 0.5f) });
}
