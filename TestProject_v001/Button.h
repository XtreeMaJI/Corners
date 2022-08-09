#pragma once
#include "SFML/Graphics.hpp"

#define SQUARE_SIZE 100

using sf::Texture;
using sf::Sprite;
using sf::Font;
using sf::Text;
using std::string;
using sf::RenderWindow;

class Button
{
public:
	struct Position
	{
		int X;
		int Y;
	};

	Position Pos;
	Sprite CurrentSprite;
	Font *CurrentFont;
	Text CurrentText;
private:
	Texture* _Tex;

public:
	Button(Position newPos, string newText);
	~Button();

	void Draw(RenderWindow *Win);

	void InitSprite();
};

