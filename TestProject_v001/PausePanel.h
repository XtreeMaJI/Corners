#pragma once
#include "Button.h"
#include "GameStateManager.h"

using sf::Texture;
using sf::Sprite;
using sf::Font;
using sf::Text;
using sf::RenderWindow;
using std::string;

class PausePanel
{
public:
	Button* ContinueB;
	Button* RestartB;
	Sprite CurrentSprite;
	Font* CurrentFont;
	Text CurrentText;
	GameStateManager::GameState GameStateBuf;//„ей ход был до паузы
private:
	Texture* _Tex;
	GameStateManager* _GSM;

public:
	PausePanel(string newText, GameStateManager* newGSM);
	~PausePanel();

	void Draw(RenderWindow* Win);

	void InitSprite();

	void HandleMouseButtonPress(sf::Vector2i MousePos);

	void PauseGame();
};

