#include "PausePanel.h"

PausePanel::PausePanel(string newText, GameStateManager* newGSM)
{
	InitSprite();
	_GSM = newGSM;

	Button::Position newPos;
	newPos.X = 3;
	newPos.Y = 2;
	ContinueB = new Button(newPos, "Продолжить");
	//Текст вылезает за рамки спрайта
	ContinueB->CurrentText.setPosition(3.3 * SQUARE_SIZE, 2.3 * SQUARE_SIZE);
	newPos.X = 3;
	newPos.Y = 4;
	RestartB = new Button(newPos, "Заново");

	newPos.X = 3 * SQUARE_SIZE;
	newPos.Y = 1 * SQUARE_SIZE;
	CurrentFont = new Font();
	CurrentFont->loadFromFile("CyrilicOld.TTF");
	CurrentText = Text(newText, *CurrentFont);
	CurrentText.setCharacterSize(48);
	CurrentText.setStyle(CurrentText.Bold);
	CurrentText.setPosition(newPos.X, newPos.Y);
}

PausePanel::~PausePanel()
{
	delete _Tex;
	delete RestartB;
	delete ContinueB;
	delete CurrentFont;
}

void PausePanel::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
	Win->draw(CurrentText);
	RestartB->Draw(Win);
	ContinueB->Draw(Win);
}

void PausePanel::InitSprite()
{
	_Tex = new Texture();
	int x = 10;
	int y = 10;
	CurrentSprite.setPosition(x, y);
	_Tex->loadFromFile("Bg.png");
	CurrentSprite.setTexture(*_Tex);
}

void PausePanel::HandleMouseButtonPress(sf::Vector2i MousePos)
{
	if (RestartB->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y))
	{
		_GSM->SetState(GameStateManager::GameState::RestartGame);
	}

	if (ContinueB->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y))
	{
		_GSM->SetState(GameStateBuf);
	}
}

void PausePanel::PauseGame()
{
	GameStateBuf = _GSM->State;
	_GSM->SetState(GameStateManager::GameState::Pause);
}
