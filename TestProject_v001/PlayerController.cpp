#include "PlayerController.h"

PlayerController::PlayerController(Piece::PieceColor newColor, std::vector<Piece*> *allPieces, GameStateManager* newGSM)
{
	Color = newColor;

	for (int i = 0; i < allPieces->size(); i++)
	{
		if (allPieces->at(i)->Color == Color)
		{
			_PlayerPieces.push_back(allPieces->at(i));
		}
	}

	_GSM = newGSM;
}

PlayerController::~PlayerController()
{
}

void PlayerController::HandleMouseButtonPress(sf::Vector2i MousePos)
{
	//≈сли игра закончилась или не началась, то ничего не делаем
	if (_GSM->State != WhiteTurn && _GSM->State != BlackTurn)
	{
		return;
	}

	//≈сли не ход игрока, то ничего не делаем
	if ((_GSM->State == WhiteTurn && Color == Piece::PieceColor::Black) ||
		(_GSM->State == BlackTurn && Color == Piece::PieceColor::White))
	{
		return;
	}

	//≈сли есть выделенна€ фигура, то провер€ем, кликнул ли игрок на один из подсвеченных квадратов
	if (SelectedPiece != nullptr)
	{
		vector<Square*> SelectedSquares = SelectedPiece->GetSelectedSquares();
		for (int i = 0; i < SelectedSquares.size(); i++)
		{
			//Ќаходитс€ ли курсор внутри границ спрайта выделенных квадратов(кроме собственного)
			if (SelectedSquares[i]->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y) &&
				SelectedSquares[i] != SelectedPiece->CurrentSquare)
			{
				Piece* MovingPieceBuf = SelectedPiece;
				DropSelection();
				MovingPieceBuf->MoveTo(SelectedSquares[i]);
				_GSM->HandOverTheMove();
				return;
			}
		}
		DropSelection();
	}
	//≈сли нет выделенной фигуры, то провер€ем, кликнул ли игрок на одну из своих фигур
	if (SelectedPiece == nullptr)
	{
		for (int i = 0; i < _PlayerPieces.size(); i++)
		{
			//Ќаходитс€ ли курсор внутри границ спрайта одной из фигур игрока
			if (_PlayerPieces[i]->CurrentSprite.getGlobalBounds().contains(MousePos.x, MousePos.y))
			{
				SelectPiece(_PlayerPieces[i]);
				return;
			}
		}
	}
}

void PlayerController::SelectPiece(Piece* newSelectedPiece)
{
	SelectedPiece = newSelectedPiece;
	SelectedPiece->Select();
}

void PlayerController::DropSelection()
{
	SelectedPiece->Deselect();
	SelectedPiece = nullptr;
}