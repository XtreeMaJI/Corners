#pragma once
#include "Square.h"
#include <vector>

using namespace std;

#define FIELD_SIZE 8

class Field
{
public:
	Square Squares[FIELD_SIZE][FIELD_SIZE];

public:
	Field();
	~Field();
	Square* GetSquare(int x, int y);
	Square* GetSquare(BaseType::PosOnField squarePos);
	void Draw(RenderWindow* Win);
};

