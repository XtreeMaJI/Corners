#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include <memory>

#define PIECES_IN_ROW 3
#define ROWS_OF_PIECES 3
#define SQUARE_SIZE 100

using namespace sf;

class BaseType
{

public:
	struct PosOnField
	{
		int X;
		int Y;
		friend bool operator== (const PosOnField &First, const PosOnField &Second);
		friend bool operator!= (const PosOnField& First, const PosOnField& Second);
	};

	PosOnField Pos;
	sf::Sprite CurrentSprite;
	Texture *_Tex;

public:
	virtual void Draw(RenderWindow* Win) = 0;
protected:
	virtual void InitSprite();
	virtual void InitTexture() = 0;
};

