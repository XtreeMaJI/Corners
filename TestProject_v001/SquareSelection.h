#pragma once
#include "BaseType.h"

class SquareSelection: public BaseType
{
public:
	SquareSelection(int x, int y);
	~SquareSelection();
	void Draw(RenderWindow* Win) override;
private:
	void InitSprite() override;
	void InitTexture() override;

};

