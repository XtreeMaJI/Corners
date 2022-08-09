#include "GameOverPanel.h"

GameOverPanel::GameOverPanel(string newText, GameStateManager* newGSM)
{
	InitSprite();
	_GSM = newGSM;

	Button::Position newPos;
	newPos.X = 3;
	newPos.Y = 2;
	RestartB = new Button(newPos, "Заново");

	newPos.X = 2 * SQUARE_SIZE;
	newPos.Y = 1 * SQUARE_SIZE;
	CurrentFont = new Font();
	CurrentFont->loadFromFile("CyrilicOld.TTF");
	CurrentText = Text(newText, *CurrentFont);
	CurrentText.setCharacterSize(48);
	CurrentText.setStyle(CurrentText.Bold);
	CurrentText.setPosition(newPos.X, newPos.Y);
}

GameOverPanel::~GameOverPanel()
{
	delete _Tex;
	delete RestartB;
	delete CurrentFont;
}

void GameOverPanel::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
	Win->draw(CurrentText);
	RestartB->Draw(Win);
}

void GameOverPanel::InitSprite()
{
	_Tex = new Texture();
	int x = 10;
	int y = 10;
	CurrentSprite.setPosition(x, y);
	_Tex->loadFromFile("Bg.png");
	CurrentSprite.setTexture(*_Tex);
}

void GameOverPanel::HandleMouseButtonPress(sf::Vector2i MousePos)
{
	if (RestartB->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y))
	{
		_GSM->SetState(GameStateManager::GameState::RestartGame);
	}
}

void GameOverPanel::SetText(string newText)
{
	CurrentText.setString(newText);
}
