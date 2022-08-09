#pragma once
#include "BaseType.h"
#include "Field.h"
#include "SquareSelection.h"

#define NUM_OF_SELECTION_SQUARES 5

using namespace sf;

class Piece : public BaseType
{
public:
	enum SelectionSide : int
	{
		Left = 0,
		Top = 1,
		Right = 2,
		Bot = 3,
		Mid = 4
	};

	enum PieceColor: int
	{
		White = 0,
		Black = 1
	};

	PieceColor Color;
	Square* CurrentSquare;

public:
	Piece(int x, int y, PieceColor newColor);
	~Piece();
	void Draw(RenderWindow* Win) override;
	void Select();
	void Deselect();
	//Устанавливаем новый квадрат для фигуры и состояние старого меняем на незанятое
	void SetNewCurrentSquare(Square* newSquare); 
	vector<Square*> GetSelectedSquares();
	void MoveTo(Square* newSquare);
private:
	void InitTexture() override;
};

