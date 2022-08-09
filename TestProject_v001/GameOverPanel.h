#pragma once
#include "Button.h"
#include "GameStateManager.h"

using sf::Texture;
using sf::Sprite;
using sf::Font;
using sf::Text;
using sf::RenderWindow;
using std::string;

class GameOverPanel
{
public:
	Button* RestartB;
	Sprite CurrentSprite;
	Font* CurrentFont;
	Text CurrentText;
private:
	Texture* _Tex;
	GameStateManager* _GSM;

public:
	GameOverPanel(string newText, GameStateManager* newGSM);
	~GameOverPanel();

	void Draw(RenderWindow* Win);

	void InitSprite();

	void HandleMouseButtonPress(sf::Vector2i MousePos);

	void SetText(string newText);
};

