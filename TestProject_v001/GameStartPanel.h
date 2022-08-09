#pragma once
#include "Button.h"
#include "GameStateManager.h"

using sf::Texture;
using sf::Sprite;
using sf::Font;
using sf::Text;
using sf::RenderWindow;
using std::string;

class GameStartPanel
{
public:
	Button* ChooseWhite;
	Button* ChooseBlack;
	Sprite CurrentSprite;
	Font *CurrentFont;
	Text CurrentText;
private:
	Texture* _Tex;
	GameStateManager* _GSM;

public:
	GameStartPanel(string newText, GameStateManager* newGSM);
	~GameStartPanel();

	void Draw(RenderWindow* Win);

	void InitSprite();

	void HandleMouseButtonPress(sf::Vector2i MousePos);

};