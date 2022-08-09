#include "Button.h"

Button::Button(Position newPos, string newText)
{
	Pos = newPos;

	InitSprite();

	CurrentFont = new Font();
	CurrentFont->loadFromFile("CyrilicOld.TTF");
	CurrentText = Text(newText, *CurrentFont);
	CurrentText.setPosition((Pos.X+0.6) * SQUARE_SIZE, (Pos.Y+0.25) * SQUARE_SIZE);
}

Button::~Button()
{
	delete _Tex;
	delete CurrentFont;
}

void Button::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
	Win->draw(CurrentText);
}

void Button::InitSprite()
{
	_Tex = new Texture();
	int x = Pos.X * SQUARE_SIZE;
	int y = Pos.Y * SQUARE_SIZE;
	CurrentSprite.setPosition(x, y);
	_Tex->loadFromFile("Button.png");
	CurrentSprite.setTexture(*_Tex);
}