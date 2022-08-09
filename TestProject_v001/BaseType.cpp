#include "BaseType.h"

void BaseType::InitSprite()
{
	_Tex = new Texture();
	int x = Pos.X * SQUARE_SIZE;
	int y = Pos.Y * SQUARE_SIZE;
	CurrentSprite.setPosition(x, y);
	InitTexture();
	CurrentSprite.setTexture(*_Tex);
}

bool operator==(const BaseType::PosOnField &First, const BaseType::PosOnField &Second)
{
	if (First.X == Second.X && First.Y == Second.Y)
	{
		return true;
	}
	return false;
}

bool operator!=(const BaseType::PosOnField &First, const BaseType::PosOnField &Second)
{
	if (First.X == Second.X && First.Y == Second.Y)
	{
		return false;
	}
	return true;
}
