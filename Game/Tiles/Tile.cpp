#include "pch.h"
#include "Tile.h"

#include "Base/App.h"
#include "Gamemodes/IGamemode.h"
#include "TileManager.h"

Tile::Tile(Vector2 spawnPosition)
	: clicked(false)
{
	button = Button::Create(SIZE, BLACK);
	auto& colors = button->GetColors();
	colors.clickedColor = BLANK;
	colors.normalColor = BLANK;
	colors.hoverColor = BLANK;
	colors.selectedColor = BLANK;

	button->CanAcceptRightClicks(true);
	button->Transform()->SetPosition(spawnPosition);
	button->GetClickEvent() += this;
	button->GameObject()->SetName("Tile" + to_string(App::debug));
	button->GameObject()->OnUpdate() += this;
}

void Tile::SetClicked()
{
	clicked = true;
	auto renderer = button->Renderer();
	renderer->SetColor(LIGHTGRAY);
}

void Tile::OnInvoke(Selectable& arg1)
{
	if (clicked) return;
	App::GetCurrentGamemodeManager()->OnTileClicked(this);
}

void Tile::OnInvoke(GameObject& arg1)
{
	auto& data = Base::Get()->GetData();
	auto height = data.screenHeight;
	auto width = data.screenWidth;
	auto y = arg1.Transform()->Position().y;
	DrawLine(0, y, width, y, BLACK);

	if (y < height + 5) return;

	if (clicked)
	{
		App::GetCurrentGamemodeManager()->OnTileOffScreen(this);
		GameObject::Destroy(&arg1);	
	}	
	else
	{
		App::GetCurrentGamemodeManager()->OnTileMissed();
		button->Renderer()->SetColor(RED);
	}
		
	

}										
