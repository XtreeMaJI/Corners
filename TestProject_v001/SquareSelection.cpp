#include "SquareSelection.h"

SquareSelection::SquareSelection(int x, int y)
{
	Pos.X = x;
	Pos.Y = y;

	InitSprite();
}

SquareSelection::~SquareSelection()
{
	delete _Tex;
}

void SquareSelection::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
}

void SquareSelection::InitSprite()
{
	_Tex = new Texture();
	float x = Pos.X * SQUARE_SIZE;
	float y = Pos.Y * SQUARE_SIZE;
	CurrentSprite.setPosition(x, y);
	InitTexture();
	CurrentSprite.setTexture(*_Tex);

	//Устанавливаем прозрачность спрайта
	sf::Color newColor = CurrentSprite.getColor();
	newColor.a = 100;
	CurrentSprite.setColor(newColor);
}


void SquareSelection::InitTexture()
{
	_Tex->loadFromFile("SelectSquareArea.png");
}
