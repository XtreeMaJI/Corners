#include "Square.h"

Square::Square()
{
}

void Square::Init(int XPos, int YPos)
{
	Pos.X = XPos;
	Pos.Y = YPos;
	if((XPos + YPos) % 2 == 0)
	{
		Color = White;
	}
	else
	{
		Color = Black;
	}

	InitSprite();
	_Selection = new SquareSelection(XPos, YPos);
}

Square::~Square()
{
	delete _Tex;
	delete _Selection;
}

void Square::Draw(RenderWindow* Win)
{
	Win->draw(CurrentSprite);
	if (IsSquareSelected)
	{
		_Selection->Draw(Win);
	}
}

void Square::SetSurroundSquares(std::vector<Square*>* newSurroundSquares)
{
	for (int i = 0; i < newSurroundSquares->size(); i++)
	{
		SurroundSquares.push_back(newSurroundSquares->at(i));
	}
}

void Square::SetBusy(bool Busyness)
{
	_IsBusyByPiece = Busyness;
}

bool Square::IsBusy()
{
	return _IsBusyByPiece;
}

void Square::Select()
{
	IsSquareSelected = true;
}

void Square::TrySelect()
{
	if (_IsBusyByPiece == false)
	{
		IsSquareSelected = true;
	}
}

void Square::Deselect()
{
	IsSquareSelected = false;
}

void Square::InitTexture()
{
	if (Color == White)
	{
		_Tex->loadFromFile("WhiteSquare.png");
	}
	else
	{
		_Tex->loadFromFile("BlackSquare.png");
	}
}
