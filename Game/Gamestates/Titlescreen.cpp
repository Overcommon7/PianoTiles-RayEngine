#include "pch.h"
#include "Titlescreen.h"

#include "Base/App.h"
#include "Tiles/TileManager.h"

void Titlescreen::Init()
{
	onMenuButtonClicked = new OnClick();
	auto& data = Base::Get()->GetData();

	auto title = TextRenderer::Create("PIANO TILES", 30.f, BLACK);
	title->Transform()->SetPosition({ (data.screenWidth * 0.5f) - (title->Bounds().Size().x * 0.5f), 35.f });

	const V2 size = { 200, 75 };
	V2 position = { (data.screenWidth * 0.5f) - (size.x * 0.5f), data.screenHeight * 0.5f };
	string message = "Pro Mode: Disabled";
	CreateButton(RED, { position.x, position.y - (size.y * 2)}, size, &message);

	for (auto name : App::GetGamemodeNames())
	{
		if (*name == "None") continue;
		CreateButton(WHITE, position, size, name);
		position.y += size.y * 1.05f;
	}

	
}

void Titlescreen::Shutdown()
{
	delete onMenuButtonClicked;
}

void Titlescreen::CreateButton(Color color, Vector2 position, Vector2 size, string* text)
{
	auto button = Button::Create(size, BLACK);
	auto textRenderer = TextRenderer::Create(*text);
	textRenderer->SetColor(color);
	auto textSize = textRenderer->Bounds().Size();

	textRenderer->Transform()->SetParent(button->Transform());
	button->Transform()->SetPosition(position);
	textRenderer->Transform()->SetLocalPosition({ 3, (size.y * 0.5f) - (textSize.y * 0.5f) });

	button->GetClickEvent() += onMenuButtonClicked;
}


void Titlescreen::OnClick::OnInvoke(Selectable& arg1)
{
	auto text = arg1.GameObject()->GetComponentInChildren<TextRenderer>();
	if (!text) return;

	if (text->GetText().find("Pro") != string::npos)
	{
		TileManager::SetProMode(!TileManager::IsProMode());
		bool pro = TileManager::IsProMode();
		text->SetColor(pro ? GREEN : RED);
		text->SetText(string("Pro Mode: ") + (pro ? "Enabled" : "Disabled"));
		return;
	}

	auto mode = magic_enum::enum_cast<App::Gamemode>(text->GetText());
	if (mode.has_value())
		App::LoadGamemode(mode.value());
}
