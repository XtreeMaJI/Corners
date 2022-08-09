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
	PieceColor Color; //���� ����� ����������

private:
	vector<Piece*> _BotPieces;
	vector<Piece*> _PiecesOnWinSquares; //������, �������� �� �������� ���������
	vector<PosOnField> WinSquarePos; //������� ������� ����� ������� - �������, �� ������� �������� ��������� ������
	Field* _GameField;
	GameStateManager* _GSM;
	vector<PosOnField> _PathCoords; //���������� ��������� ����, ���� �� ���������� ��������� ��������
	Piece* _MovingPiece = nullptr;
	int _PosOnPath = 0; // �������, ��� ��������� ������������� ������ �� ����

public:
	BotController(PieceColor newColor, vector<Piece*> allPieces, Field* newField, GameStateManager* newGSM);

	void MakeMove();
private:
	void InitWinSquares();
	//�������� ������ ����� ����������, ��������������� �� �������� � ������� �������� ������
	vector<Piece*> GetVectSortedByDistance();
	bool IsElemInVect(Piece * elem, vector<Piece*> vect);
	bool IsElemInVect(PathCoord elem, vector<PathCoord> vect);
	//�������� ���������� �������� ��������� ������ � currentCoord
	vector<PathCoord> GetAvailableCoords(PathCoord currentCoord);
	//�������� ���������� �� ������� ��������� �� �������
	PathCoord GetElemFromPathCoordVect(PosOnField curPos, vector<PathCoord> vect);
	vector<PosOnField> GetReversedVect(vector<PosOnField> vect);
	void RemoveElemFromVect(Piece* elem, vector<Piece*> *vect);
	//�������� ��������� �������� ����� � currentPiece
	vector<Square*> GetAvailableSquares(Piece* currentPiece);
	//��������� �� ���� �� ����� �� ������� �������� ������. ���� ��, �� ��� ���������� _MovingPiece
	bool IsSomePieceOnWinSquare();
	void PushElemForward(PosOnField elem, vector<PosOnField> *vect);

	//�������� ������� ������ � ����������� �������� ������. ���� �� ����������, �� ���������� false
	bool TryMoveForward();
	//�������� �� �����-������ �� ����� ������� �������� ������. ���� ��, �� ������� � � ������ �� ������
	void CheckWinSquare();
	//�������� ������ �� ������ ����� ����, ���� ����� ������� �� ����������
	Piece* GetNotBlockedPiece();
	//�������� �������� ��� ������ �������� �� ����������� � �������� ������
	vector<Square*> GetEmptyForwardSquares(Piece* currentPiece);
	//����� �������� ���� ��� ������
	vector<PosOnField> FindBypassPath(Piece* currentPiece, PosOnField tarPos);
	//������� MovingPiece �� ����������� 
	bool TryMoveAlongPath();

};

