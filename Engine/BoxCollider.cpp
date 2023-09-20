#include "pch.h"
#include "BoxCollider.h"

#include "GameObject.h"
#include "Bounds.h"
#include "Structs.h"


namespace
{
    inline Vector2 RotatePoint(Vector2 point, float angleDegrees)
    {
        float sinRotation = std::sin(angleDegrees * DEG2RAD);
        float cosRotation = std::cos(angleDegrees * DEG2RAD);

        auto x = point.x + cosRotation;
        auto y = point.y + sinRotation;

        return Vector2(x, y);
    }

    inline bool CheckCollision(const vector<Vector2>& rectangle, float angleDegrees, Vector2 point)
    {
        Vector2 rotatedPoint = RotatePoint(point, -angleDegrees);

        float minX = std::min(std::min(rectangle[0].x, rectangle[1].x), std::min(rectangle[2].x, rectangle[3].x));
        float maxX = std::max(std::max(rectangle[0].x, rectangle[1].x), std::max(rectangle[2].x, rectangle[3].x));
        float minY = std::min(std::min(rectangle[0].y, rectangle[1].y), std::min(rectangle[2].y, rectangle[3].y));
        float maxY = std::max(std::max(rectangle[0].y, rectangle[1].y), std::max(rectangle[2].y, rectangle[3].y));

        bool isInside = (rotatedPoint.x >= minX && rotatedPoint.x <= maxX) && (rotatedPoint.y >= minY && rotatedPoint.y <= maxY);

        return isInside;
    }

    inline vector<Vector2> GetPoints(Rectangle rectangle)
    {
        vector<Vector2> values(4, Vector2());

        values[0] = Vector2(rectangle.x, rectangle.y);
        values[1] = Vector2(rectangle.x + rectangle.width, rectangle.y);
        values[2] = Vector2(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
        values[3] = Vector2(rectangle.x, rectangle.y + rectangle.height);

        return values;
    }

    inline float GetMinValue(const vector<float>& values)
    {
        float min = values[0];
        for (int i = 1; i < values.size(); i++)
        {
            if (values[i] < min)
                min = values[i];
        }
        return min;
    }

    inline float GetMaxValue(const vector<float>& values)
    {
        float max = values[0];
        for (int i = 1; i < values.size(); i++)
        {
            if (values[i] > max)
                max = values[i];
        }
        return max;
    }

    inline vector<float> CalculateProjection(const vector<Vector2>& corners, Vector2 axis)
    {
        vector<float> projection(4, 0);
        for (int i = 0; i < 4; i++)
        {
            projection[i] = Vector2DotProduct(corners[i], axis);
        }
        return projection;
    }

    inline bool IsOverlapOnAxis(const vector<Vector2>& corners1, const vector<Vector2>& corners2, Vector2 axis)
    {
        auto projection1 = CalculateProjection(corners1, axis);
        auto projection2 = CalculateProjection(corners2, axis);

        float minP1 = GetMinValue(projection1);
        float maxP1 = GetMaxValue(projection1);
        float minP2 = GetMinValue(projection2);
        float maxP2 = GetMaxValue(projection2);

        return maxP1 >= minP2 && maxP2 >= minP1;
    }

    inline bool IsOverlap(const vector<Vector2>& corners1, const vector<Vector2>& corners2)
    {
        if (!IsOverlapOnAxis(corners1, corners2, Vector2(1, 0)))
            return false;
        if (!IsOverlapOnAxis(corners1, corners2, Vector2(0, 1)))
            return false;

        return true;
    }

    inline vector<Vector2> RotateRectangle(Rectangle rectangle, float angleDegrees)
    {
        Vector2 origin = Vector2(rectangle.width * 0.5f, rectangle.height * 0.5f);
        float sinRotation = std::sin(angleDegrees * DEG2RAD);
        float cosRotation = std::cos(angleDegrees * DEG2RAD);
        float X = rectangle.x + origin.x;
        float Y = rectangle.y + origin.y;
        float dX = -origin.x;
        float dy = -origin.y;

        vector<Vector2> rotatedRectangle(4, Vector2());

        rotatedRectangle[0].x = X + dX * cosRotation - dy * sinRotation;
        rotatedRectangle[0].y = Y + dX * sinRotation + dy * cosRotation;

        rotatedRectangle[1].x = X + (dX + rectangle.width) * cosRotation - dy * sinRotation;
        rotatedRectangle[1].y = Y + (dX + rectangle.width) * sinRotation + dy * cosRotation;

        rotatedRectangle[2].x = X + dX * cosRotation - (dy + rectangle.height) * sinRotation;
        rotatedRectangle[2].y = Y + dX * sinRotation + (dy + rectangle.height) * cosRotation;

        rotatedRectangle[3].x = X + (dX + rectangle.width) * cosRotation - (dy + rectangle.height) * sinRotation;
        rotatedRectangle[3].y = Y + (dX + rectangle.width) * sinRotation + (dy + rectangle.height) * cosRotation;

        return rotatedRectangle;
    }

    inline bool CheckCollision(Rectangle rectangle1, float angle1Degrees, Rectangle rectangle2, float angle2Degrees)
    {
        auto rect1 = RotateRectangle(rectangle1, angle1Degrees);
        auto rect2 = RotateRectangle(rectangle2, angle2Degrees);

        if (!IsOverlap(rect1, rect2))
            return false;

        return IsOverlap(rect2, rect1);
    }
    
}

RayEngine::BoxCollider::BoxCollider(RayEngine::GameObject* gameObject, Vector2 size)
	: Collider(gameObject, "BoxCollider", size, Shape::Square)
{
    	
}

Rectangle RayEngine::BoxCollider::GetCollider() const
{
	RayEngine::Bounds bounds = Bounds();
	Vector2 position = bounds.Min();
	Vector2 size = bounds.Size();
	return Rectangle(position.x, position.y, size.x, size.y);
}

bool RayEngine::BoxCollider::IsColliding(Vector2 point) const
{
    if (!isActive) return false;

    if (gameObject->Transform()->Rotation() == 0)
        return CheckCollisionPointRec(point, GetCollider());

    return CheckCollision(GetPoints(GetCollider()), gameObject->Transform()->Rotation(), point);
}

bool RayEngine::BoxCollider::IsColliding(Circle circle) const
{
    if (!isActive) return false;

    if (gameObject->Transform()->Rotation() == 0)
        return CheckCollisionCircleRec(circle.position, circle.radius, GetCollider());

    auto point = RotatePoint(circle.position, gameObject->Transform()->Rotation());
    return CheckCollisionCircleRec(point, circle.radius, GetCollider());
}

bool RayEngine::BoxCollider::IsColliding(Rectangle rectangle) const
{
    if (!isActive) return false;

    if (gameObject->Transform()->Rotation() == 0)
        return CheckCollisionRecs(rectangle, GetCollider());

    return CheckCollision(GetCollider(), gameObject->Transform()->Rotation(), rectangle, 0);
}

bool RayEngine::BoxCollider::IsColliding(const BoxCollider& collider) const
{
    if (!isActive) return false;

    if (gameObject->Transform()->Rotation() == 0)
        return CheckCollisionRecs(collider.GetCollider(), GetCollider());

    return CheckCollision(GetCollider(), gameObject->Transform()->Rotation(), collider.GetCollider(), collider.gameObject->Transform()->Rotation());
}
