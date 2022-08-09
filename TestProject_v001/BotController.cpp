#include "BotController.h"

BotController::BotController(PieceColor newColor, vector<Piece*> allPieces, Field* newField, GameStateManager* newGSM)
{
	Color = newColor;
	_GameField = newField;
	_GSM = newGSM;

	for (int i = 0; i < allPieces.size(); i++)
	{
		if (allPieces[i]->Color == Color)
		{
			_BotPieces.push_back(allPieces[i]);
		}
	}

	InitWinSquares();
}

void BotController::InitWinSquares()
{
	if (Color == PieceColor::Black)
	{
		for (int i = 0; i < ROWS_OF_PIECES; i++)
		{
			for (int j = 0; j < PIECES_IN_ROW; j++)
			{
				PosOnField Pos;
				Pos.X = FIELD_SIZE - 1 - i;
				Pos.Y = FIELD_SIZE - 1 - j;
				WinSquarePos.push_back(Pos);
			}
		}
	}
	
	if (Color == PieceColor::White)
	{
		for (int i = 0; i < ROWS_OF_PIECES; i++)
		{
			for (int j = 0; j < PIECES_IN_ROW; j++)
			{
				PosOnField Pos;
				Pos.X = i;
				Pos.Y = j;
				WinSquarePos.push_back(Pos);
			}
		}
	}

}

void BotController::MakeMove()
{
	//≈сли игра закончилась или не началась, то ничего не делаем
	if (_GSM->State != WhiteTurn && _GSM->State != BlackTurn)
	{
		return;
	}

	//≈сли не ход бота, то ничего не делаем
	if ((_GSM->State == WhiteTurn && Color == PieceColor::Black) ||
		(_GSM->State == BlackTurn && Color == PieceColor::White))
	{
		return;
	}

	//ƒвижение по обходному пути, если фигура была блокирована
	if (TryMoveAlongPath() == true)
	{
		CheckWinSquare();
		_GSM->HandOverTheMove();
		return;
	}

	//ƒвигатьс€ в направлении нужного квадрата
	if (_MovingPiece != nullptr &&
		TryMoveForward() == true)
	{
		CheckWinSquare();
		_GSM->HandOverTheMove();
		return;
	}
	else //≈сли не получаетс€, то переходим к следующей фигуре
	{
		//≈сли одна из фигур уже находитс€ на текущей победной клетке, то пытаемс€ сделать ход ещЄ раз
		if (IsSomePieceOnWinSquare() == true)
		{
			CheckWinSquare();
			MakeMove();
			return;
		}
		_MovingPiece = GetNotBlockedPiece();
		if (_MovingPiece != nullptr)
		{
			TryMoveForward();
			CheckWinSquare();
			_GSM->HandOverTheMove();
			return;
		}
	}

	//≈сли не осталось фигур, которые могут двигатьс€ вперЄд, то ищем обходной путь
	if (_MovingPiece == nullptr)
	{
		for (int i = 0; i < _BotPieces.size(); i++)
		{
			_PathCoords = FindBypassPath(_BotPieces[i], WinSquarePos[0]);
			_MovingPiece = _BotPieces[i];
			if (_PathCoords.empty() == false && TryMoveAlongPath() == true)
			{
				CheckWinSquare();
				_GSM->HandOverTheMove();
				return;
			}
		}
	}

	//≈сли нет обходных путей ни дл€ одной из фигур, то движемс€ назад самой ближней
	vector<Piece*> SortedVect = GetVectSortedByDistance();
	for (int i = 0; i < SortedVect.size(); i++)
	{
		vector<Square*> AvailableSquares = GetAvailableSquares(SortedVect[i]);
		if (AvailableSquares.empty() == false)
		{
			SortedVect[i]->MoveTo(AvailableSquares[0]);
			_GSM->HandOverTheMove();
			return;
		}
	}

	//≈сли все фигуры на непобедных клетках заблокированы со всех сторон, то убираем фигуру с победной клетки
	for (int i = 0; i < _PiecesOnWinSquares.size(); i++)
	{
		vector<Square*> AvailableSquares = GetAvailableSquares(_PiecesOnWinSquares[i]);
		if (AvailableSquares.empty() == false)
		{
			Piece* PieceBuf = _PiecesOnWinSquares[i];
			_BotPieces.push_back(PieceBuf);
			PushElemForward(PieceBuf->CurrentSquare->Pos, &WinSquarePos);
			RemoveElemFromVect(PieceBuf, &_PiecesOnWinSquares);
			PieceBuf->MoveTo(AvailableSquares[0]);
			_GSM->HandOverTheMove();
			return;
		}
	}

	//≈сли добрались сюда, то доступных ходов у бота нет
	if (Color == PieceColor::White)
	{
		_GSM->SetState(GameStateManager::WhiteBlocked);
	}
	else
	{
		_GSM->SetState(GameStateManager::BlackBlocked);
	}
	return;

}

vector<Piece*> BotController::GetVectSortedByDistance()
{
	vector<Piece*> SortedVector;
	PosOnField targetPos = WinSquarePos[0];
	int Distance = 0; //–ассто€ние в количестве ходов между полем фигуры и целевым полем 
	int MinDistance = 16;
	Piece* PieceBuf;
	for (int i = 0; i < _BotPieces.size(); i++)
	{
		MinDistance = 16;
		for (int j = 0; j < _BotPieces.size(); j++)
		{
			Distance = abs(_BotPieces[j]->Pos.X - targetPos.X) + abs(_BotPieces[j]->Pos.Y - targetPos.Y);
			if (Distance < MinDistance && 
				IsElemInVect(_BotPieces[j], SortedVector) == false)
			{
				MinDistance = Distance;
				PieceBuf = _BotPieces[j];
			}
		}
		SortedVector.push_back(PieceBuf);
	}
	return SortedVector;
}

bool BotController::IsElemInVect(Piece* elem, vector<Piece*> vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		if (elem == vect[i])
		{
			return true;
		}
	}
	return false;
}

bool BotController::IsElemInVect(PathCoord elem, vector<PathCoord> vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		if (elem.CurCoord == vect[i].CurCoord)
		{
			return true;
		}
	}
	return false;
}

vector<BotController::PathCoord> BotController::GetAvailableCoords(PathCoord currentCoord)
{
	vector<PathCoord> AvailableCoords;
	Square* CurSquare = _GameField->GetSquare(currentCoord.CurCoord);
	vector<Square*> AvailableSquares = CurSquare->SurroundSquares;
	for (int i = 0; i < AvailableSquares.size(); i++)
	{
		if (AvailableSquares[i]->IsBusy() == false)
		{
			PathCoord BufCoord;
			BufCoord.CurCoord = AvailableSquares[i]->Pos;
			BufCoord.PrevCoord = currentCoord.CurCoord;
			AvailableCoords.push_back(BufCoord);
		}
	}
	return AvailableCoords;
}

BotController::PathCoord BotController::GetElemFromPathCoordVect(PosOnField curPos, vector<PathCoord> vect)
{
	for (int i = 0; i< vect.size(); i++)
	{
		if (vect[i].CurCoord == curPos)
		{
			return vect[i];
		}
	}
	PathCoord ErrorCase;
	ErrorCase.CurCoord.X = -1;
	ErrorCase.CurCoord.Y = -1;
	ErrorCase.PrevCoord.X = -1;
	ErrorCase.PrevCoord.Y = -1;
	return ErrorCase;
}

vector<PosOnField> BotController::GetReversedVect(vector<PosOnField> vect)
{
	vector<PosOnField> NewVect;
	for (int i=vect.size()-1; i >= 0; i--)
	{
		NewVect.push_back(vect[i]);
	}
	return NewVect;
}

void BotController::RemoveElemFromVect(Piece* elem, vector<Piece*> *vect)
{
	vector<Piece*> OldVect = *vect;
	vect->clear();
	for (int i = 0; i < OldVect.size(); i++)
	{
		if (OldVect[i] != elem)
		{
			vect->push_back(OldVect[i]);
		}
	}
}

vector<Square*> BotController::GetAvailableSquares(Piece* currentPiece)
{
	vector<Square*> AvailableSquares;
	vector<Square*> SurroundSquares = currentPiece->CurrentSquare->SurroundSquares;
	for (int i = 0; i < SurroundSquares.size(); i++)
	{
		if (SurroundSquares[i]->IsBusy() == false)
		{
			AvailableSquares.push_back(SurroundSquares[i]);
		}
	}
	return AvailableSquares;
}

bool BotController::IsSomePieceOnWinSquare()
{
	if (WinSquarePos.empty() == true || _BotPieces.empty() == true)
	{
		return false;
	}
	vector<Piece*> SortedVector = GetVectSortedByDistance();

	for (int i =0; i < SortedVector.size(); i++)
	{
		if (SortedVector[i]->Pos == WinSquarePos[0])
		{
			_MovingPiece = SortedVector[i];
			return true;
		}
	}
	
	return false;
}

void BotController::PushElemForward(PosOnField elem, vector<PosOnField>* vect)
{
	if (vect->empty() == true)
	{
		return;
	}
	vector<PosOnField> OldVect = *vect;
	vect->clear();
	vect->push_back(elem);
	for (int i = 0; i < OldVect.size(); i++)
	{
		vect->push_back(OldVect[i]);
	}
}

bool BotController::TryMoveForward()
{
	vector<Square*> ForwardSquares = GetEmptyForwardSquares(_MovingPiece);

	if (ForwardSquares.empty() == false)
	{
		_MovingPiece->MoveTo(ForwardSquares[0]);
		return true;
	}

	return false;
}

void BotController::CheckWinSquare()
{
	if (_MovingPiece->Pos.X == WinSquarePos[0].X &&
		_MovingPiece->Pos.Y == WinSquarePos[0].Y)
	{
		_PiecesOnWinSquares.push_back(_MovingPiece);
		RemoveElemFromVect(_MovingPiece, &_BotPieces);
		_MovingPiece = nullptr;
		WinSquarePos.erase(WinSquarePos.begin());
		_PathCoords.clear();
	}
}

Piece* BotController::GetNotBlockedPiece()
{
	vector<Piece*> SortedVector = GetVectSortedByDistance();
	for (int i = 0; i < SortedVector.size(); i++)
	{
		vector<Square*> ForwardSquares = GetEmptyForwardSquares(SortedVector[i]);
		if (ForwardSquares.empty() == false)
		{
			return SortedVector[i];
		}
	}
	return nullptr;
}

vector<Square*> BotController::GetEmptyForwardSquares(Piece* currentPiece)
{
	vector<Square*> ForwardSquares;

	int PieceX = currentPiece->Pos.X;
	int PieceY = currentPiece->Pos.Y;
	int SquareX = WinSquarePos[0].X;
	int SquareY = WinSquarePos[0].Y;

	if (PieceX > SquareX)
	{
		Square* LeftSquare = _GameField->GetSquare(PieceX - 1, PieceY);
		if (LeftSquare != nullptr && LeftSquare->IsBusy() == false)
		{
			ForwardSquares.push_back(LeftSquare);
		}
	}

	if (PieceX < SquareX)
	{
		Square* RightSquare = _GameField->GetSquare(PieceX + 1, PieceY);
		if (RightSquare != nullptr && RightSquare->IsBusy() == false)
		{
			ForwardSquares.push_back(RightSquare);
		}
	}

	if (PieceY < SquareY)
	{
		Square* TopSquare = _GameField->GetSquare(PieceX, PieceY + 1);
		if (TopSquare != nullptr && TopSquare->IsBusy() == false)
		{
			ForwardSquares.push_back(TopSquare);
		}
	}

	if (PieceY > SquareY)
	{
		Square* DownSquare = _GameField->GetSquare(PieceX, PieceY - 1);
		if (DownSquare != nullptr && DownSquare->IsBusy() == false)
		{
			ForwardSquares.push_back(DownSquare);
		}
	}

	return ForwardSquares;
}

//—начала делаем поиск в ширину и, если достигли искомой клетки, то 
//составл€ем путь двига€сь обратно по предыдущим координатам каждой клетки на пути
vector<PosOnField> BotController::FindBypassPath(Piece* currentPiece, PosOnField tarPos)
{
	vector<PosOnField> Bypass;
	int SearchDeph = 64; //—колько возможных ходов просматриваем, прежде чем объ€вить, что пути нет
	vector<PathCoord> AllAchievableCoords; //¬се координаты, которых можем достичь из начальной точки 
	vector<PathCoord> NewCoords; //¬се координаты, достигнутые на последнем сделанном шаге
	PathCoord PathStart;
	PathCoord PathEnd;
	
	PathStart.CurCoord = currentPiece->Pos;
	PathStart.PrevCoord = currentPiece->Pos;
	NewCoords.push_back(PathStart);

	PathEnd.CurCoord = tarPos;
	PathEnd.PrevCoord = tarPos;

	//»щем все возможные клетки, до которых можем добратьс€
	while (SearchDeph != 0)
	{
		SearchDeph--;

		for (int i = 0; i < NewCoords.size(); i++)
		{
			AllAchievableCoords.push_back(NewCoords[i]);
		}

		if (IsElemInVect(PathEnd, AllAchievableCoords) == true)
		{
			break;
		}

		vector<PathCoord> NewCoordsBuf = NewCoords;
		NewCoords.clear();
		for (int i = 0; i < NewCoordsBuf.size(); i++)
		{
			vector<PathCoord> AvailableCoords = GetAvailableCoords(NewCoordsBuf[i]);
			for (int j = 0; j < AvailableCoords.size(); j++)
			{
				if (IsElemInVect(AvailableCoords[j], AllAchievableCoords) == false &&
					IsElemInVect(AvailableCoords[j], NewCoords) == false)
				{
					NewCoords.push_back(AvailableCoords[j]);
				}
			}
		}
	}

	if (IsElemInVect(PathEnd, AllAchievableCoords) == false)
	{
		return Bypass;
	}

	//»дЄм от финальной точки обратно к началу и строим путь
	PathCoord CurrentCoord = GetElemFromPathCoordVect(PathEnd.CurCoord, AllAchievableCoords);
	if (CurrentCoord.CurCoord.X == -1)
	{
		Bypass.clear();
		return Bypass;
	}
	Bypass.push_back(CurrentCoord.CurCoord);
	while (CurrentCoord.CurCoord != PathStart.CurCoord)
	{
		CurrentCoord = GetElemFromPathCoordVect(CurrentCoord.PrevCoord, AllAchievableCoords);
		if (CurrentCoord.CurCoord.X == -1)
		{
			Bypass.clear();
			return Bypass;
		}
		Bypass.push_back(CurrentCoord.CurCoord);
	}
	Bypass = GetReversedVect(Bypass);

	return Bypass;
}

bool BotController::TryMoveAlongPath()
{
	if (_PathCoords.empty() == true || _MovingPiece == nullptr)
	{
		return false;
	}

	for (int i = 0; i < _PathCoords.size()-1; i++)
	{
		if (_MovingPiece->Pos == _PathCoords[i])
		{
			if (_GameField->GetSquare(_PathCoords[i + 1])->IsBusy() == false)
			{
				_MovingPiece->MoveTo(_GameField->GetSquare(_PathCoords[i + 1]));
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
