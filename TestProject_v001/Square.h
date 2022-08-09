#pragma once
#include "BaseType.h"
#include "SquareSelection.h"

class Piece;

class Square: public BaseType
{
public:
	enum SquareColor: int 
	{
		White = 0,
		Black = 1
	};

public:
	SquareColor Color;
	std::vector<Square*> SurroundSquares;
	bool IsSquareSelected = false;

private:
	bool _IsBusyByPiece = false;
	SquareSelection* _Selection;
	

public:
	Square();
	~Square();

	void Init(int XPos, int YPos);

	void Draw(RenderWindow* Win) override;
	void SetSurroundSquares(std::vector<Square*>* newSurroundSquares);

	void SetBusy(bool Busyness);
	bool IsBusy();

	void Select();
	void TrySelect();
	void Deselect();

private:
	void InitTexture() override;
	
};

