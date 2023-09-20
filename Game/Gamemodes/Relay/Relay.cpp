#include "pch.h"
#include "Relay.h"

#include "Gamestates/Retry.h"

void Relay::OnStart()
{
	IGamemode::OnStart();

	timer = TIME;
	tilesPressed = 0;
	totalTiles = 0;
	showRefresh = false;
	refreshTimer = 0;

	timerDisplay = TextRenderer::Create(Format(TIME, 3) + "\"", 35, GREEN);
	timeOut = TextRenderer::Create("TIME OUT", 50, RED);
	refreshDisplay = TextRenderer::Create(to_string((int)TIME) + "\"", 100, GREEN);

	
	scoreDisplay = GameObject::Create({0, 0}, 0, "ScoreDisplay")->
		AddComponent<SpriteRenderer>(Shape::Square, V2(1, 7), RED, 50);

	auto screen = Base::Get()->GetScreenDimensions();

	timeOut->Transform()->SetPosition({
		(screen.x * 0.5f) - (timeOut->Bounds().Size().x * 0.5f),
		(screen.y * 0.5f) - (timeOut->Bounds().Size().y * 0.5f) });
		
	timerDisplay->Transform()->SetPosition({
		(screen.x * 0.5f) - (timerDisplay->Bounds().Size().x * 0.5f), 15 });

	timeOut->SetSortingLayer(50);
	timerDisplay->SetSortingLayer(50);
	refreshDisplay->SetSortingLayer(50);
	refreshDisplay->GameObject()->SetActive(false);
	timeOut->GameObject()->SetActive(false);
}

void Relay::OnEnd()
{
	IGamemode::OnEnd();
}

Relay* Relay::Get()
{
	if (!rush)
		rush = new Relay();
	return rush;
}

void Relay::SetUpRetry()
{
	Base::Get()->SetClearColor(RED);
	Retry::OnStart(to_string(totalTiles), Name());
}

void Relay::OnUpdate()
{
	IGamemode::OnUpdate();

	if (failed || !started) return;

	if (showRefresh)
	{
		refreshDisplay->Transform()->TranslateYPos(-150 * Time::DeltaTime());
		auto color = refreshDisplay->GetColor();
		color.a =  (1 - (refreshTimer / REFRESH_TIME)) * 255;
		refreshDisplay->SetColor(color);
		refreshTimer += Time::DeltaTime();

		if (refreshTimer >= REFRESH_TIME)
		{
			showRefresh = false;
			refreshTimer = 0;
			refreshDisplay->GameObject()->SetActive(false);
		}
	}

	timer -= Time::DeltaTime();
	timerDisplay->SetText(Format(timer, 3) + "\"");
	timerDisplay->Transform()->SetXPosition(
		(Base::Get()->GetData().screenWidth * 0.5f) -
		(timerDisplay->Bounds().Size().x * 0.5f));

	float t = InverseLerp(0, TIME, TIME - timer);
	timerDisplay->SetColor(LerpColor(GREEN, RED, t));

	if (timer > 0) return;

	failed = true;
	timeOut->GameObject()->SetActive(true);
}

void Relay::Shutdown()
{
	delete rush;
}

void Relay::OnTileMissed()
{
	IGamemode::OnTileMissed();
}

void Relay::OnTileClicked(Tile* tile)
{
	auto size = tiles.size();
	IGamemode::OnTileClicked(tile);
	if (size == tiles.size()) return;

	for (const auto& tile : tiles)
		tile->Transform()->TranslateYPos(Tile::SIZE.y);

	++totalTiles;
	++tilesPressed;

	if (tilesPressed >= TILES_TO_REFRESH)
	{
		tilesPressed = 0;
		timer = TIME;
		showRefresh = true;
		refreshTimer = 0;
		refreshDisplay->GameObject()->SetActive(true);

		auto screen = Base::Get()->GetScreenDimensions();

		refreshDisplay->Transform()->SetPosition({
			(screen.x * 0.5f) - (refreshDisplay->Bounds().Size().x * 0.5f),
			(screen.y * 0.5f) - (refreshDisplay->Bounds().Size().y * 0.5f) });	

		refreshDisplay->SetColor(GREEN);
	}

	auto width = Base::Get()->GetData().screenWidth;
	scoreDisplay->Transform()->SetScaleX((tilesPressed / (float)TILES_TO_REFRESH) * (float)width);
	scoreDisplay->SetColor(LerpColor(RED, GREEN, tilesPressed / (float)TILES_TO_REFRESH));
}
