#include "Field.h"

Field::Field()
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			Squares[i][j].Init(i, j);
		}
	}

	//Устанавливаем для каждого квадрата, квадраты, находящиеся по бокам и сверху и снизу от него
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			std::vector<Square*> SurroundSquares;
			if (i - 1 >= 0)
			{
				SurroundSquares.push_back(&Squares[i-1][j]);
			}
			if (j - 1 >= 0)
			{
				SurroundSquares.push_back(&Squares[i][j - 1]);
			}
			if (i + 1 < FIELD_SIZE)
			{
				SurroundSquares.push_back(&Squares[i + 1][j]);
			}
			if (j + 1 < FIELD_SIZE)
			{
				SurroundSquares.push_back(&Squares[i][j + 1]);
			}
			Squares[i][j].SetSurroundSquares(&SurroundSquares);
		}
	}
}

Field::~Field()
{
}

Square* Field::GetSquare(int x, int y)
{
	if (x>=0 && x<FIELD_SIZE && 
		y>=0 && y<FIELD_SIZE)
	{
		return &Squares[x][y];
	}
	return nullptr;
}

Square* Field::GetSquare(BaseType::PosOnField squarePos)
{
	return GetSquare(squarePos.X, squarePos.Y);
}

void Field::Draw(RenderWindow* Win)
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			Squares[i][j].Draw(Win);
		}
	}
}
