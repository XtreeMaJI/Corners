#include "GameStateManager.h"

GameStateManager::GameStateManager(GameState newGameState, vector<Piece*> allPieces, Field* newField)
{
	State = newGameState;
	_Pieces = allPieces;
	_GameField = newField;
	InitWinPos();
}

void GameStateManager::HandOverTheMove()
{
	if (IsSomeoneWon() == true)
	{
		return;
	}

	if (State == WhiteTurn)
	{
		State = BlackTurn;
		return;
	}
	
	if (State == BlackTurn)
	{
		State = WhiteTurn;
		return;
	}
}

void GameStateManager::InitWinPos()
{
	for (int i = 0; i < _Pieces.size(); i++)
	{
		if (_Pieces[i]->Color == PieceColor::White)
		{
			_BlackWinPos.push_back(_Pieces[i]->Pos);
		}

		if (_Pieces[i]->Color == PieceColor::Black)
		{
			_WhiteWinPos.push_back(_Pieces[i]->Pos);
		}
	}
}

bool GameStateManager::IsSomeoneWon()
{
	if (IsWhiteWon() == true)
	{
		State = WhiteWon;
		return true;
	}

	if (IsBlackWon() == true)
	{
		State = BlackWon;
		return true;
	}
	return false;
}

bool GameStateManager::IsWhiteWon()
{
	for (int i = 0; i < _Pieces.size(); i++)
	{
		if (_Pieces[i]->Color == PieceColor::White && 
			IsElemInVect(_Pieces[i]->Pos, _WhiteWinPos) == false)
		{
			return false;
		}
	}
	return true;
}

bool GameStateManager::IsBlackWon()
{
	for (int i = 0; i < _Pieces.size(); i++)
	{
		if (_Pieces[i]->Color == PieceColor::Black &&
			IsElemInVect(_Pieces[i]->Pos, _BlackWinPos) == false)
		{
			return false;
		}
	}
	return true;
}

bool GameStateManager::IsElemInVect(PosOnField elem, vector<PosOnField> vect)
{
	if (vect.empty() == true)
	{
		return false;
	}

	for (int i = 0; i < vect.size(); i++)
	{
		if (elem == vect[i])
		{
			return true;
		}
	}

	return false;
}

void GameStateManager::SetState(GameState newState)
{
	State = newState;
}
