#pragma once
#include "LevelManager.h"
#include "Piece.h"

LevelManager::LevelManager(RenderWindow* RenderWin)
{
	_Win = RenderWin;
	GameField = new Field();
	CreatePieces();
	_GSM = new GameStateManager(ChoosingColor, Pieces, GameField);
	_GameStartPanel = new GameStartPanel("Выберите цвет фигур", _GSM);
	_GameOverPanel = new GameOverPanel(" ", _GSM);
	_PausePanel = new PausePanel("Пауза", _GSM);
	//TestFunc();
}

void LevelManager::InitColors()
{
	_PC = new PlayerController(_GSM->PlayerColor, &Pieces, _GSM);
	if (_GSM->PlayerColor == PieceColor::White)
	{
		_BC = new BotController(PieceColor::Black, Pieces, GameField, _GSM);
	}
	else
	{
		_BC = new BotController(PieceColor::White, Pieces, GameField, _GSM);
	}
	
	_GSM->SetState(WhiteTurn);
}

LevelManager::~LevelManager()
{
	delete GameField;
	delete _PC;
	delete _GSM;
	delete _GameStartPanel;
	delete _GameOverPanel;
	delete _PausePanel;
	delete _BC;
}

void LevelManager::ReinitGame()
{
	delete GameField;
	delete _GSM;
	delete _PC;
	delete _BC;
	delete _PausePanel;
	delete _GameStartPanel;
	delete _GameOverPanel;
	Pieces.clear();

	GameField = new Field();
	CreatePieces();
	_GSM = new GameStateManager(ChoosingColor, Pieces, GameField);
	_GameStartPanel = new GameStartPanel("Выберите цвет фигур", _GSM);
	_GameOverPanel = new GameOverPanel(" ", _GSM);
	_PausePanel = new PausePanel("Пауза", _GSM);
}

void LevelManager::RedrawWindow()
{
	if (_GSM->State == ChoosingColor)
	{
		_GameStartPanel->Draw(_Win);
	}

	if(_GSM->State == WhiteTurn || _GSM->State == BlackTurn)
	{
		GameField->Draw(_Win);
		DrawPieces();
	}

	if (_GSM->State == WhiteWon || _GSM->State == BlackWon ||
		_GSM->State == WhiteBlocked || _GSM->State == BlackBlocked)
	{
		_GameOverPanel->Draw(_Win);
	}

	if (_GSM->State == Pause)
	{
		_PausePanel->Draw(_Win);
	}
}

void LevelManager::HandleEvent(Event ev)
{
	if (ev.type == sf::Event::Closed)
	{
		_Win->close();
	}

	if ((_GSM->State == WhiteTurn || _GSM->State == BlackTurn) &&
		ev.type == sf::Event::MouseButtonPressed && 
		ev.key.code == sf::Mouse::Left)
	{
		sf::Vector2i MousePos = sf::Mouse::getPosition(*_Win);
		_PC->HandleMouseButtonPress(MousePos);
	}

	if ((_GSM->State == ChoosingColor) &&
		ev.type == sf::Event::MouseButtonPressed &&
		ev.key.code == sf::Mouse::Left)
	{
		sf::Vector2i MousePos = sf::Mouse::getPosition(*_Win);
		_GameStartPanel->HandleMouseButtonPress(MousePos);
	}

	if ((_GSM->State == BlackWon || _GSM->State == WhiteWon ||
		 _GSM->State == WhiteBlocked || _GSM->State == BlackBlocked) &&
		ev.type == sf::Event::MouseButtonPressed &&
		ev.key.code == sf::Mouse::Left)
	{
		sf::Vector2i MousePos = sf::Mouse::getPosition(*_Win);
		_GameOverPanel->HandleMouseButtonPress(MousePos);
			
	}

	if ((_GSM->State == Pause) &&
		ev.type == sf::Event::MouseButtonPressed &&
		ev.key.code == sf::Mouse::Left)
	{
		sf::Vector2i MousePos = sf::Mouse::getPosition(*_Win);
		_PausePanel->HandleMouseButtonPress(MousePos);
	}

	if ((_GSM->State == WhiteTurn || _GSM->State == BlackTurn) &&
		ev.type == sf::Event::KeyPressed &&
		ev.key.code == sf::Keyboard::Key::Escape)
	{
		_PausePanel->PauseGame();
	}

}

void LevelManager::Update()
{
	switch (_GSM->State)
	{
		case WhiteTurn:
			if (_BC->Color == PieceColor::White)
			{
				_BC->MakeMove();
			}
			break;
		case BlackTurn:
			if (_BC->Color == PieceColor::Black)
			{
				_BC->MakeMove();
			}
			break;
		case WhiteWon:
			_GameOverPanel->SetText("Белые победили");
			break;
		case BlackWon:
			_GameOverPanel->SetText("Чёрные победили");
			break;
		case ChoosingColor:
			break;
		case InitingColors:
			InitColors();
			break;
		case RestartGame:
			ReinitGame();
			break;
		case BlackBlocked:
			_GameOverPanel->SetText("Все чёрные фигуры\n\tблокированы");
			break;
		case WhiteBlocked:
			_GameOverPanel->SetText("Все белые фигуры\n\tблокированы");
			break;
		default:
			break;
	}
}

void LevelManager::CreatePieces()
{
	//Чёрные фигуры
	for (int i = 0; i < ROWS_OF_PIECES; i++)
	{
		for (int j = 0; j < PIECES_IN_ROW; j++)
		{
			Pieces.push_back(new Piece(i, j, Piece::PieceColor::Black));
		}
	}

	//Белые фигуры
	for (int i = 0; i < ROWS_OF_PIECES; i++)
	{
		for (int j = 0; j < PIECES_IN_ROW; j++)
		{
			int x = FIELD_SIZE - 1 - i;
			int y = FIELD_SIZE - 1 - j;
			Pieces.push_back(new Piece(x, y, Piece::PieceColor::White));
		}
	}

	//Добавляем стартовые квадраты, на которых они находятся, каждой фигуре
	for (int i = 0; i < Pieces.size(); i++)
	{
		int x = Pieces[i]->Pos.X;
		int y = Pieces[i]->Pos.Y;
		Pieces[i]->SetNewCurrentSquare(GameField->GetSquare(x, y));
	}
}

void LevelManager::DrawPieces()
{
	for (int i = 0; i < Pieces.size(); i++)
	{
		Pieces[i]->Draw(_Win);
	}
}

void LevelManager::TestFunc()
{
	int array[FIELD_SIZE][FIELD_SIZE] = {	{0, 0, 0, 0, 0, 0, 0, 0},
											{0, 0, 0, 0, 0, 0, 0, 0},
											{0, 0, 0, 0, 0, 0, 0, 0},
											{0, 0, 0, 0, 2, 2, 2, 0},
											{0, 0, 0, 0, 0, 2, 2, 2},
											{0, 0, 0, 0, 2, 1, 1, 1},
											{0, 0, 0, 0, 2, 1, 1, 1},
											{0, 0, 0, 0, 2, 1, 1, 1} };
	
	for (int PieceNum = 0; PieceNum < 18; PieceNum++)
	{
		Pieces[PieceNum]->CurrentSquare->SetBusy(false);
		Pieces[PieceNum]->CurrentSquare = nullptr;
	}

	for (int PieceNum = 0; PieceNum < 18; PieceNum++)
	{
		bool IsSquareFound = false;
		for (int i = 0; i < FIELD_SIZE; i++)
		{
			if (IsSquareFound == true)
			{
				break;
			}
			for (int j = 0; j < FIELD_SIZE; j++)
			{
				if (array[i][j] == 1 && 
					Pieces[PieceNum]->Color == Piece::PieceColor::White &&
					GameField->GetSquare(j,i)->IsBusy() == false)
				{
					Pieces[PieceNum]->MoveTo(GameField->GetSquare(j, i));
					IsSquareFound = true;
					
					break;
				}

				if (array[i][j] == 2 &&
					Pieces[PieceNum]->Color == Piece::PieceColor::Black &&
					GameField->GetSquare(j, i)->IsBusy() == false)
				{
					Pieces[PieceNum]->MoveTo(GameField->GetSquare(j, i));
					IsSquareFound = true;
					break;
				}
			}
		}
	}

	//GameField->GetSquare(Pieces[0]->Pos)->Select();

}
