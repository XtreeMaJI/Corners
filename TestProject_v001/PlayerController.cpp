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
	//���� ���� ����������� ��� �� ��������, �� ������ �� ������
	if (_GSM->State != WhiteTurn && _GSM->State != BlackTurn)
	{
		return;
	}

	//���� �� ��� ������, �� ������ �� ������
	if ((_GSM->State == WhiteTurn && Color == Piece::PieceColor::Black) ||
		(_GSM->State == BlackTurn && Color == Piece::PieceColor::White))
	{
		return;
	}

	//���� ���� ���������� ������, �� ���������, ������� �� ����� �� ���� �� ������������ ���������
	if (SelectedPiece != nullptr)
	{
		vector<Square*> SelectedSquares = SelectedPiece->GetSelectedSquares();
		for (int i = 0; i < SelectedSquares.size(); i++)
		{
			//��������� �� ������ ������ ������ ������� ���������� ���������(����� ������������)
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
	//���� ��� ���������� ������, �� ���������, ������� �� ����� �� ���� �� ����� �����
	if (SelectedPiece == nullptr)
	{
		for (int i = 0; i < _PlayerPieces.size(); i++)
		{
			//��������� �� ������ ������ ������ ������� ����� �� ����� ������
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