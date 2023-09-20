#pragma once
#include "pch.h"

struct Circle
{
    Vector2 position;
    float radius;
};

namespace RayEngine
{
    inline static constexpr const Color colors[] =
    {
       LIGHTGRAY,
       GRAY     ,
       DARKGRAY ,
       YELLOW   ,
       GOLD     ,
       ORANGE   ,
       PINK     ,
       RED      ,
       MAROON   ,
       GREEN    ,
       LIME     ,
       DARKGREEN,
       SKYBLUE  ,
       BLUE     ,
       DARKBLUE ,
       PURPLE   ,
       VIOLET   ,
       DARKPURPLE,
       BEIGE    ,
       BROWN    ,
       DARKBROWN,
       WHITE    ,
       BLACK    ,
       BLANK    ,
       MAGENTA  ,
       RAYWHITE ,
    };

    template<class T>
    concept Number = std::is_floating_point_v<T> || std::is_integral_v<T>;

    template<class T>
    concept Integral = std::is_integral_v<T>;

    template<class T>
    concept FloatingPoint = std::is_floating_point_v<T>;

    template<Integral T>
    static T Random(T includedMax, T includedMin = 0, const std::pair<T, T>& ExcludeRange = { 0, 0 }, const vector<T>& exclude = {})
    {
        bool range = false;
        bool isValid = true;
        T value{};
        if (ExcludeRange.first != ExcludeRange.second) range = true;
        std::random_device r;

        if (includedMax < includedMin)
        {
            T temp = includedMax;
            includedMax = includedMin;
            includedMin = temp;
        }

        do
        {
            isValid = true;
            std::mt19937 gen(r());
            std::uniform_int_distribution<T> dist(includedMin, includedMax);
            value = dist(gen);
            for (const auto& i : exclude)
                if (i == value)
                {
                    isValid = false;
                    break;
                }
            if (range && isValid)
                if (value >= ExcludeRange.first && value <= ExcludeRange.second)
                    isValid = false;
        } while (!isValid);
        return value;
    }

    static void DrawRectangle(const Rectangle& r, const Color& c = BLACK)
    {
        DrawRectangle((int)r.x, (int)r.y, (int)r.width, (int)r.height, c);
    }

    static void DrawRectangleLines(const Rectangle& r, const Color& c = BLACK)
    {
        DrawRectangleLines((int)r.x, (int)r.y, (int)r.width, (int)r.height, c);
    }

    static void DrawCircle(const Circle& circle, const Color& c = BLACK)
    {
        DrawCircle((int)circle.position.x, (int)circle.position.y, circle.radius, c);
    }

    static void DrawCircleLines(const Circle& circle, const Color& c = BLACK)
    {
        DrawCircleLines((int)circle.position.x, (int)circle.position.y, circle.radius, c);
    }

    template<Number N>
    static void DrawText(const N num, const Vector2 position, const float size, const Color color = BLACK)
    {
        DrawText(to_string(num).c_str(), position.x, position.y, size, color);
    }

    static void DrawText(const string_view& text, const Vector2 position, const float size, const Color color = BLACK)
    {
        DrawText(text.data(), position.x, position.y, size, color);
    }

    template<Number N>
    static void DrawText(Font font, const N num, const Vector2 position, const float size, const Color color = BLACK)
    {
        DrawTextEx(font, to_string(num).c_str(), position, size, 1.f, color);
    }

    static void DrawText(Font font, const string_view& text, const Vector2 position, const float size, const Color color = BLACK)
    {
        DrawTextEx(font, text.data(), position, size, 1.f, color);
    }

    static string ToLowerString(const string& s)
    {
        string temp;
        temp.reserve(s.length());
        for (auto& c : s)
            temp.push_back(tolower(c));
        return temp;
    }

    static string ToUpperString(const string& s)
    {
        string temp;
        temp.reserve(s.length());
        for (auto& c : s)
            temp.push_back(toupper(c));
        return temp;
    }

    static bool IsDigit(const string& str)
    {
        short i = 0;
        if (str.front() == '+' || str.front() == '-') ++i;
        for (; i < str.length(); i++)
            if (!isdigit(str[i])) return false;
        return true;
    }

    static bool IsFloat(const string& str)
    {
        short numOfDeciamls = 0;
        short i = 0, j = 0;
        if (str.front() == '+' || str.front() == '-') ++i;
        if (str.back() == 'f') ++j;
        for (; i < str.length() - j; i++)
        {
            if (str[i] != '.' && !isdigit(str[i])) return false;
            if (str[i] == '.') ++numOfDeciamls;
            if (numOfDeciamls > 1) return false;
        }
        return true;
    }

    static bool TryParse(const string& str, float& num)
    {
        if (IsFloat(str))
        {
            num = stof(str);
            return true;
        }
        return false;
    }

    static bool TryParse(const string& str, int& num)
    {
        if (IsDigit(str))
        {
            num = stoi(str);
            return true;
        }
        return false;
    }

    static bool TryParse(const vector<string>& params, vector<float>& values)
    {
        values.resize(params.size(), 0);
        for (short i = 0; i < params.size(); i++)
            if (!TryParse(params[i], values[i])) return false;
        return true;
    }

    static bool TryParse(const vector<string>& params, vector<int>& values)
    {
        values.resize(params.size(), 0);
        for (short i = 0; i < params.size(); i++)
            if (!TryParse(params[i], values[i])) return false;
        return true;
    }

    static string Format(float num, int decimalPlaces)
    {
        string value = to_string(num);
        size_t pos = value.find('.');
        if (pos == string::npos) return value;
        ++decimalPlaces;
        if (pos + decimalPlaces >= value.length()) return value;
        return value.erase(pos + decimalPlaces);
        
    }

    static string ToString(Vector2 vec, int decimalPlaces = 2)
    {
        return '[' + Format(vec.x, decimalPlaces) + ", " + Format(vec.y, decimalPlaces) + ']';
    }

    static Color RandomColor()
    {
        return colors[Random(25)];
    }

    static bool Approximately(float x, float y)
    {
        return std::abs(x - y) < 0.01f * std::max(std::abs(x), std::abs(y));
    }

    static bool Equals(Color a, Color b)
    {
        return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
    }

    static bool Equals(Vector2 a, Vector2 b)
    {
        return Approximately(a.x, b.x) && Approximately(a.y, b.y);
    }
}
