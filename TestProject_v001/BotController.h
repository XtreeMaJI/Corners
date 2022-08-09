#pragma once
#include "Piece.h"
#include "Field.h"
#include "GameStateManager.h"

#define WhiteTurn GameStateManager::GameState::WhiteTurn
#define BlackTurn GameStateManager::GameState::BlackTurn
#define	PosOnField	BaseType::PosOnField
#define	PieceColor	Piece::PieceColor

using std::vector;

class BotController
{
private:
	struct PathCoord
	{
		PosOnField CurCoord;
		PosOnField PrevCoord;
	};

public:
	PieceColor Color; //Цвет фигур компьютера

private:
	vector<Piece*> _BotPieces;
	vector<Piece*> _PiecesOnWinSquares; //Фигуры, дошедшие до победных квадратов
	vector<PosOnField> WinSquarePos; //Нулевой элемент этого вектора - квадрат, на который пытаемся поставить фигуру
	Field* _GameField;
	GameStateManager* _GSM;
	vector<PosOnField> _PathCoords; //Координаты обходного пути, если не получается добраться напрямую
	Piece* _MovingPiece = nullptr;
	int _PosOnPath = 0; // Счётчик, где находится передвигаемая фигура на пути

public:
	BotController(PieceColor newColor, vector<Piece*> allPieces, Field* newField, GameStateManager* newGSM);

	void MakeMove();
private:
	void InitWinSquares();
	//Получить вектор фигур компьютера, отсортированный по близости к текущей победной клетке
	vector<Piece*> GetVectSortedByDistance();
	bool IsElemInVect(Piece * elem, vector<Piece*> vect);
	bool IsElemInVect(PathCoord elem, vector<PathCoord> vect);
	//Получить координаты соседних незанятых клеток к currentCoord
	vector<PathCoord> GetAvailableCoords(PathCoord currentCoord);
	//Получить координату из вектора координат по позиции
	PathCoord GetElemFromPathCoordVect(PosOnField curPos, vector<PathCoord> vect);
	vector<PosOnField> GetReversedVect(vector<PosOnField> vect);
	void RemoveElemFromVect(Piece* elem, vector<Piece*> *vect);
	//Получить незанятые квадраты рядом с currentPiece
	vector<Square*> GetAvailableSquares(Piece* currentPiece);
	//Находится ли одна из фигур на текущей победной клетке. Если да, то она становится _MovingPiece
	bool IsSomePieceOnWinSquare();
	void PushElemForward(PosOnField elem, vector<PosOnField> *vect);

	//Пытаемся двигать фигуру в направлении победной клетки. Если не получается, то возвращаем false
	bool TryMoveForward();
	//Достигла ли какая-нибудь из фигур текущей победной клетки. Если да, то убираем её и фигуру из списка
	void CheckWinSquare();
	//Получить фигуру из списка фигур бота, путь вперёд которой не блокирован
	Piece* GetNotBlockedPiece();
	//Получить соседние для фигуры квадраты по направлению к победной клетке
	vector<Square*> GetEmptyForwardSquares(Piece* currentPiece);
	//Найти обходной путь для фигуры
	vector<PosOnField> FindBypassPath(Piece* currentPiece, PosOnField tarPos);
	//Двигаем MovingPiece по координатам 
	bool TryMoveAlongPath();

};

