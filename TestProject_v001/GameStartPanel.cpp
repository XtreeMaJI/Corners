#include "GameStartPanel.h"

GameStartPanel::GameStartPanel(string newText, GameStateManager* newGSM)
{
	InitSprite();
	_GSM = newGSM;

	Button::Position newPos;
	newPos.X = 3;
	newPos.Y = 2;
	ChooseWhite = new Button(newPos, "Белые");
	newPos.X = 3;
	newPos.Y = 4;
	ChooseBlack = new Button(newPos, "Чёрные");

	newPos.X = 2 * SQUARE_SIZE;
	newPos.Y = 1 * SQUARE_SIZE;
	CurrentFont = new Font();
	CurrentFont->loadFromFile("CyrilicOld.TTF");
	CurrentText = Text(newText, *CurrentFont);
	CurrentText.setCharacterSize(48);
	CurrentText.setStyle(CurrentText.Bold);
	CurrentText.setPosition(newPos.X, newPos.Y);
}

GameStartPanel::~GameStartPanel()
{
	delete _Tex;
	delete ChooseWhite;
	delete ChooseBlack;
	delete CurrentFont;
}

void GameStartPanel::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
	Win->draw(CurrentText);
	ChooseWhite->Draw(Win);
	ChooseBlack->Draw(Win);
}

void GameStartPanel::InitSprite()
{
	_Tex = new Texture();
	int x = 10;
	int y = 10;
	CurrentSprite.setPosition(x, y);
	_Tex->loadFromFile("Bg.png");
	CurrentSprite.setTexture(*_Tex);
}

void GameStartPanel::HandleMouseButtonPress(sf::Vector2i MousePos)
{
	if (ChooseWhite->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y))
	{
		_GSM->PlayerColor = PieceColor::White;
		_GSM->SetState(GameStateManager::GameState::InitingColors);
	}

	if (ChooseBlack->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y))
	{
		_GSM->PlayerColor = PieceColor::Black;
		_GSM->SetState(GameStateManager::GameState::InitingColors);
	}
}