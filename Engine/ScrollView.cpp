#include "pch.h"
#include "ScrollView.h"

#include "BoxCollider.h"
#include "Bounds.h"
#include "GameObject.h"

#include "Renderer.h"

RayEngine::Scrollview::Scrollview(RayEngine::GameObject* gameObject, Vector2 size, float scrollSpeed)
	: Scrollview(gameObject, size, {}, scrollSpeed)
{

}

RayEngine::Scrollview::Scrollview(RayEngine::GameObject* gameObject, Vector2 size, const vector<RayEngine::Transform*>& items, float scrollSpeed)
	: Component(gameObject, "Scrollview"), scrollSpeed(scrollSpeed)
{
	viewport = GameObject::Create()->AddComponent<BoxCollider>(size);
	content = GameObject::Create()->AddComponent<BoxCollider>(size);

	viewport->Transform()->SetParent(transform, false);
	content->Transform()->SetParent(viewport->Transform(), false);

	AddItems(items);
}

void RayEngine::Scrollview::AddItem(RayEngine::Transform* item)
{
	const auto bounds = content->Bounds();
	const auto max = bounds.Max();
	const auto min = bounds.Min();
	const auto size = bounds.Size();

	auto position = item->Position();

	item->SetParent(content->Transform());
	item->SetXPosition(std::clamp(position.x, min.x, max.x));

	if (item->Position().y > max.y) {
		auto y = item->Position().y - min.y;
		Renderer* renderer;
		if (item->GameObject()->TryGetComponent(renderer))
			y += renderer->Bounds().Size().y;
		content->SetSize({ size.x, y });
	}
		
	UpdateViewables();
	onItemAdded.Invoke(*this);
}

void RayEngine::Scrollview::AddItems(const vector<RayEngine::Transform*>& items)
{
	const auto bounds = content->Bounds();
	const auto max = bounds.Max();
	const auto min = bounds.Min();
	const auto size = bounds.Size();

	for (auto item : items)
	{
		
		auto position = item->Position();
		item->SetParent(content->Transform());
		item->SetXPosition(std::clamp(position.x, min.x, max.x));

		if (item->Position().y < max.y)	continue;

		auto y = item->Position().y - min.y;
		Renderer* renderer;
		if (item->GameObject()->TryGetComponent(renderer))
			y += renderer->Bounds().Size().y;
		content->SetSize({ size.x, y });
	}

	UpdateViewables();
	onItemAdded.Invoke(*this);
}

void RayEngine::Scrollview::SetSize(Vector2 size)
{
	content->SetSize(size);
}

RayEngine::Scrollview* RayEngine::Scrollview::Create(Vector2 size, float scrollSpeed, const vector<RayEngine::Transform*>& items)
{
	return GameObject::Create()->AddComponent<Scrollview>(size, items, scrollSpeed);
}

void RayEngine::Scrollview::Update()
{
	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::None) return;
	if (!viewport->IsColliding(Mouse::Position())) return;


	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Up &&
		content->Bounds().Max().y <= viewport->Bounds().Max().y) return;
	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Down &&
		content->Bounds().Min().y >= viewport->Bounds().Min().y) return;

	float extra = 100.f;
	if (Mouse::Wheel::Vertical() == Mouse::Wheel::Movement::Up)
		extra = -extra;

	content->Transform()->TranslateYPos(scrollSpeed * extra * Time::DeltaTime());

	UpdateViewables();
}

void RayEngine::Scrollview::UpdateViewables()
{
	const auto bounds = viewport->Bounds();
	const auto max = bounds.Max();
	const auto min = bounds.Min();

	for (int i = 0; i < content->Transform()->ChildCount(); i++)
	{
		auto item = content->Transform()->GetChild(i);

		Renderer* renderer = item->GameObject()->GetComponentInChildren<Renderer>(true);
		if (renderer != nullptr)
		{
			auto temp = renderer->Bounds();
			auto t_min = temp.Min().y;
			auto t_max = temp.Max().y;

			if (t_max < min.y || t_min > max.y)
				item->GameObject()->SetActive(false);
			else item->GameObject()->SetActive(true);
		}
		else
		{
			float y = item->Position().y;

			if (y > max.y || y < min.y)
				item->GameObject()->SetActive(false);
			else item->GameObject()->SetActive(true);
		}
	}
}

//void RayEngine::Scrollview::LateDraw()
//{
//	DrawRectangleLines(viewport->GetCollider(), PINK);
//	DrawRectangleLines(content->GetCollider(), RED);
//}
