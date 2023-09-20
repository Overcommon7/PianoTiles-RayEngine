#include "pch.h"
#include "Mouse.h"
#include "GameTime.h"

using namespace RayEngine;

void Mouse::Wheel::Update()
{
    delta = GetMouseWheelMoveV();

    if (delta.x == 0) horizantal = Movement::None;
    else horizantal = delta.x < 0 ? Movement::Left : Movement::Right;

    if (delta.y == 0) vertical = Movement::None;
    else vertical = delta.y < 0 ? Movement::Down : Movement::Up;
}

void Mouse::Update()
{
	Wheel::Update();


    auto temp = GetMousePosition();
    if (!(temp.x == 0 && position.x == -1))
    {
        position = temp;
    }
    delta = GetMouseDelta();

    left.isPressed = IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT);
    right.isPressed = IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT);

    left.isDoubleClicked = false;
    right.isDoubleClicked = false;

    if (left.firstClick)
    {
        left.timer += Time::DeltaTime();
        if (left.timer <= DOUBLE_CLICK_TIME)
        {
            if (left.isPressed)
            {
                left.isDoubleClicked = true;
                left.firstClick = false;
            }
        }
        else
        {
            left.firstClick = false;
            left.timer = 0;
        }
    }
    else if (left.isPressed)
    {
        left.firstClick = true;
        left.timer = 0;
    }

    if (right.firstClick)
    {
        right.timer += Time::DeltaTime();
        if (right.timer <= DOUBLE_CLICK_TIME)
        {
            if (right.isPressed)
            {
                right.isDoubleClicked = true;
                right.firstClick = false;
            }
        }
        else
        {
            right.firstClick = false;
            right.timer = 0;
        }
    }
    else if (right.isPressed)
    {
        right.firstClick = true;
        right.timer = 0;
    }

    left.isDown = IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT);
    right.isDown = IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT);
}
