#include "Piece.h"

Piece::Piece(int x, int y, PieceColor newColor)
{
	Color = newColor;

	Pos.X = x;
	Pos.Y = y;

	InitSprite();
}

Piece::~Piece()
{
	delete _Tex;
}

void Piece::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
}

void Piece::Select()
{
	CurrentSquare->Select();
	for (int i = 0; i < CurrentSquare->SurroundSquares.size(); i++)
	{
		CurrentSquare->SurroundSquares[i]->TrySelect();
	}
}

void Piece::Deselect()
{
	CurrentSquare->Deselect();
	for (int i = 0; i < CurrentSquare->SurroundSquares.size(); i++)
	{
		CurrentSquare->SurroundSquares[i]->Deselect();
	}
}

void Piece::SetNewCurrentSquare(Square* newSquare)
{
	if (CurrentSquare != nullptr)
	{
		CurrentSquare->SetBusy(false);
	}
	CurrentSquare = newSquare;
	CurrentSquare->SetBusy(true);
}

vector<Square*> Piece::GetSelectedSquares()
{
	vector<Square*> SelectedSquares;

	if (CurrentSquare->IsSquareSelected == true)
	{
		SelectedSquares.push_back(CurrentSquare);
	}

	for (int i = 0; i < CurrentSquare->SurroundSquares.size(); i++)
	{
		if (CurrentSquare->SurroundSquares[i]->IsSquareSelected == true)
		{
			SelectedSquares.push_back(CurrentSquare->SurroundSquares[i]);
		}
	}
	return SelectedSquares;
}

void Piece::MoveTo(Square* newSquare)
{
	SetNewCurrentSquare(newSquare);
	Pos.X = newSquare->Pos.X;
	Pos.Y = newSquare->Pos.Y;
	CurrentSprite.setPosition(Pos.X * SQUARE_SIZE, Pos.Y * SQUARE_SIZE);
}

void Piece::InitTexture()
{
	if (Color == White)
	{
		_Tex->loadFromFile("WhitePiece.png");
	}
	else
	{
		_Tex->loadFromFile("BlackPiece.png");
	}
}


