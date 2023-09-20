#pragma once

namespace RayEngine
{
    class Mouse final
    {
    public:
        struct Button
        {
            bool isDown = false;
            bool isPressed = false;
            bool isDoubleClicked = false;
            bool firstClick = false;
            float timer = 0;
        };

        inline static const float DOUBLE_CLICK_TIME = 0.35f;

        inline static Vector2 Position() { return position; }
        inline static Vector2 Delta() { return delta; }
        inline static Rectangle Collider() { return Rectangle(position.x, position.y, size.x, size.y); }

        inline static bool IsLeftDown() { return left.isDown; }
        inline static bool IsLeftClicked() { return left.isPressed; }
        inline static bool IsLeftDoubleClicked() { return left.isDoubleClicked; }
        inline static bool IsRightDown() { return right.isDown; }
        inline static bool IsRightClicked() { return right.isPressed; }
        inline static bool IsRightDoubleClicked() { return right.isDoubleClicked; }

        inline static void SetSize(Vector2 size) { Mouse::size = size; }
        static void Update();
    private:
        inline static Vector2 delta;
        inline static Vector2 position = { -1 , -1 };
        inline static Vector2 size = { 3, 3 };
        inline static Button left;
        inline static Button right;
    public:
        Mouse() = delete;
        Mouse(const Mouse& m) = delete;
        Mouse(const Mouse&& m) = delete;
        Mouse& operator=(const Mouse& m) = delete;
        Mouse& operator=(const Mouse&& m) = delete;

        struct Wheel
        {
            enum class Movement
            {
                None = 0,
                Up,
                Down,
                Left,
                Right
            };

            static void Update();
            inline static float DeltaX() { return delta.x; }
            inline static float DeltaY() { return delta.y; }
            inline static Vector2 Delta() { return delta; }
            inline static Movement Horizantal() { return horizantal; }
            inline static Movement Vertical() { return vertical; }

            Wheel() = delete;
            Wheel(const Wheel& w) = delete;
            Wheel(const Wheel&& w) = delete;
            Wheel& operator=(const Wheel& w) = delete;
            Wheel& operator=(const Wheel&& w) = delete;

        private:
            inline static Vector2 delta;
            inline static Movement horizantal;
            inline static Movement vertical;
        };
    };
}

