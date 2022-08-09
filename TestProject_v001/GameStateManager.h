#pragma once
#include "Piece.h"
#include "Field.h"

#define	PosOnField	BaseType::PosOnField
#define	PieceColor	Piece::PieceColor

using std::vector;

class GameStateManager
{
public:
	enum GameState : int
	{
		WhiteTurn = 0,
		BlackTurn = 1,
		WhiteWon = 2,
		BlackWon = 3,
		ChoosingColor = 4,
		InitingColors = 5,
		RestartGame = 6,
		Pause = 7,
		WhiteBlocked = 8,
		BlackBlocked = 9
	};

	GameState State = WhiteTurn;
	PieceColor PlayerColor = PieceColor::White;

private:
	vector<Piece*> _Pieces;
	Field* _GameField;

	vector<PosOnField> _WhiteWinPos;
	vector<PosOnField> _BlackWinPos;
public:
	GameStateManager(GameState newGameState, vector<Piece*> allPieces, Field* newField);

	//Передать ход другой стороне
	void HandOverTheMove();
	void SetState(GameState newState);
private:
	void InitWinPos();
	bool IsSomeoneWon(); //Проверить не находятся ли позиции фигур одного из игроков на победных местах
	bool IsWhiteWon();
	bool IsBlackWon();

	bool IsElemInVect(PosOnField elem, vector<PosOnField> vect);
};

