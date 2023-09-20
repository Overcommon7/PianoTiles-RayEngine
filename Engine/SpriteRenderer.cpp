#include "pch.h"
#include "SpriteRenderer.h"

#include "Transform.h"
#include "Bounds.h"


namespace
{
	inline Vector2 RotatePoint(float angle, Vector2 center, Vector2 point)
	{
		angle = angle * DEG2RAD;
		return 
		{
			(point.x - center.x) * std::cos(angle) - (point.y - center.y) * std::sin(angle) + center.x,
			(point.x - center.x) * std::sin(angle) + (point.y - center.y) * std::cos(angle) + center.y 
		};
	}
}

Texture2D RayEngine::SpriteRenderer::GetTexture(size_t hash)
{
	for (const auto& item : textures)
	{
		if (item.first == hash)
			return item.second;
	}
	return Texture2D();
}

bool RayEngine::SpriteRenderer::HasTexture(size_t hash)
{
	for (const auto& item : textures)
	{
		if (item.first == hash)
			return true;
	}
	return false;
}

void RayEngine::SpriteRenderer::DrawRectangle(Vector2 position, Vector2 size, float roatation, Color color)
{
	Rectangle rectangle = Rectangle(position.x + (size.x * 0.5f), position.y + (size.y * 0.5f), size.x, size.y);
	Vector2 origin = Vector2(size.x * 0.5f, size.y * 0.5f);
	DrawRectanglePro(rectangle, origin, roatation, color);
}

void RayEngine::SpriteRenderer::DrawCircle(const RayEngine::Bounds& bounds, Color color)
{
	auto center = bounds.Center();
	::DrawCircle(center.x, center.y, bounds.Size().x * 0.5f, color);
}

void RayEngine::SpriteRenderer::DrawTriangle(const RayEngine::Bounds& bounds, float rotation, Color color)
{
	auto max = bounds.Max();
	auto min = bounds.Min();
	auto center = bounds.Center();

	auto v1 = Vector2(center.x, min.y), v2 = Vector2(min.x, max.y), v3 = max;

	if (rotation != 0)
	{
		v1 = RotatePoint(rotation, center, v1);
		v2 = RotatePoint(rotation, center, v2);
		v3 = RotatePoint(rotation, center, v3);
	}

	::DrawTriangle(v1, v2, v3, color);
}

RayEngine::SpriteRenderer::SpriteRenderer(RayEngine::GameObject* gameObject, Shape shape, Vector2 size, Color tint, int sortingLayer)
	: Renderer(gameObject, sortingLayer, tint, "SpriteRenderer"), size(size), shape(shape)
{
	hash = 0;
	this->index = -1;
}

RayEngine::SpriteRenderer::SpriteRenderer(RayEngine::GameObject* gameObject, string filename, Vector2 size, Color tint, int sortingLayer)
	: Renderer(gameObject, sortingLayer, tint, "SpriteRenderer")
{
	if (!fs::exists(filename))
	{
		filename.insert(0, Base::Get()->GetData().rootDirectory.generic_string());
		if (!fs::exists(filename))
			throw std::exception("File Not Found");
	}

	auto hash = fs::hash_value(filename);
	Texture2D texture = {};

	this->index = -1;

	for (int i = 0 ; i < textures.size(); i++)
	{
		if (textures[i].first == hash)
		{
			texture = textures[i].second;
			this->index = i;
			break;
		}
	}

	if (texture.id == 0)
	{
		this->index = (int)textures.size();
		texture = LoadTexture(filename.c_str());
		textures.push_back({ hash, texture});
	}
		
	this->hash = hash;

	if (size.x == -1 || size.y == -1)
		this->size = Vector2(texture.width, texture.height);
	else
		this->size = size;
}

void RayEngine::SpriteRenderer::InternalDraw() const
{
	auto bounds = Bounds();
	auto size = bounds.Size();

	if (index == -1 || hash == 0)
	{
		switch (shape)
		{
		case RayEngine::Shape::Square:
			DrawRectangle(transform->Position(), size, transform->Rotation(), color);
			break;
		case RayEngine::Shape::Circle:
			DrawCircle(bounds, color);
			break;
		case RayEngine::Shape::Triangle:
			DrawTriangle(bounds, transform->Rotation(), color);
			break;
		}	
	}
	else
	{
		auto center = bounds.Center();
		Texture2D& image = textures[index].second;

		Rectangle source = Rectangle(0.0f, 0.0f, image.width, image.height);
		Rectangle dest = Rectangle(center.x, center.y, size.x, size.y);
		Vector2 origin = Vector2(dest.width * 0.5f, dest.height * 0.5f);
		DrawTexturePro(image, source, dest, origin, transform->Rotation(), color);
	}
}

RayEngine::Bounds RayEngine::SpriteRenderer::Bounds() const
{
	return RayEngine::Bounds(transform->Position(), size, transform->Scale());
}

void RayEngine::SpriteRenderer::Shutdown()
{
	for (const auto& [hash, texture] : textures)
		UnloadTexture(texture);

}

void RayEngine::SpriteRenderer::SetTexture(size_t hash, bool resize)
{
	auto texture = GetTexture(hash);
	if (texture.id == 0) return;

	this->hash = hash;
	if (!resize) return;
	size = Vector2(texture.width, texture.height);
}

void RayEngine::SpriteRenderer::SetTexture(string filepath, bool resize)
{

	if (!fs::exists(filepath))
	{
		filepath.insert(0, Base::Get()->GetData().rootDirectory.generic_string());
		if (!fs::exists(filepath))
			throw std::exception("File Not Found");
	}

	auto hash = fs::hash_value(filepath);

	auto texture = GetTexture(hash);
	if (texture.id == 0)
	{
		texture = LoadTexture(filepath.c_str());
		index = textures.size();
		textures.push_back({ hash, texture });
	}


	if (!resize) return;
	size = Vector2(texture.width, texture.height);
}

void RayEngine::SpriteRenderer::SetTexture(Image image, bool resize)
{
	SetTexture(LoadTextureFromImage(image), resize);
	
}

void RayEngine::SpriteRenderer::SetTexture(const Texture2D& texture, bool resize)
{
	int i = 0;
	for (const auto& [hash, text] : textures) {
		if (texture.id == text.id)
		{
			this->hash = hash;
			index = i;
			if (resize)
				size = Vector2(texture.width, texture.height);
			return;
		}
		++i;
	}

	hash = Random<size_t>(ULLONG_MAX);
	index = textures.size();
	textures.push_back({ hash, texture });
}
