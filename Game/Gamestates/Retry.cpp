#include "pch.h"
#include "Retry.h"

#include "Tiles/TileManager.h"
#include "Base/App.h"

void Retry::Init()
{
	auto screen = Base::Get()->GetScreenDimensions();

	onClick = new OnClick();

	mode = TextRenderer::Create("Arcade", 25, BLACK);
	mode->Transform()->SetPosition({ 0, 175 });

	proModeText = TextRenderer::Create("ProMode", 15, BLACK)->GameObject();
	proModeText->Transform()->SetPosition({ screen.x - 150, 50 });
	proModeText->SetActive(false);

	score = TextRenderer::Create("0", 50, BLACK);
	score->CenterBetween(0, screen.y, TextRenderer::CenterType::Y);

	retry = CreateButton(75, "Retry");
	exit = CreateButton(screen.x - (75 * 2), "Exit");
}

void Retry::OnStart(const string& score, const string& gamemode)
{
	auto screen = Base::Get()->GetScreenDimensions();

	Retry::score->SetText(score);
	Retry::score->CenterBetween(0, screen.x);
	
	mode->SetText(gamemode);
	mode->CenterBetween(0, screen.x);

	proModeText->SetActive(TileManager::IsProMode());
}

void Retry::Shutdown()
{
	delete onClick;
}

Button* Retry::CreateButton(float xPosition, const string& name)
{
	auto screen = Base::Get()->GetScreenDimensions();

	auto text = TextRenderer::Create(name, 20, BLACK);
	auto button = Button::Create({ 75, 30 }, RED);
	text->Transform()->SetParent(button->Transform());
	text->Transform()->SetLocalPosition({ 5, 5 });
	text->SetSortingLayer(5);
	button->Transform()->SetPosition({ xPosition, screen.y - 250 });
	button->GetClickEvent() += onClick;

	return button;
}

void Retry::OnClick::OnInvoke(Selectable& arg1)
{
	if (*arg1.GameObject() == *retry->GameObject())
	{
		App::LoadGamemode(App::CurrentGamemode());
	}
	else if (*arg1.GameObject() == *exit->GameObject())
	{
		App::SetGamestate(App::Gamestate::Titlescreen);
	}
	
}
