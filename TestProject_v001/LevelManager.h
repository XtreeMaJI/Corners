#pragma once
#include "Field.h"
#include "Piece.h"
#include "PlayerController.h"
#include "BotController.h"
#include "GameStartPanel.h"
#include "GameOverPanel.h"
#include "PausePanel.h"
#include <vector>

#define WhiteTurn GameStateManager::GameState::WhiteTurn
#define BlackTurn GameStateManager::GameState::BlackTurn
#define WhiteWon GameStateManager::GameState::WhiteWon
#define BlackWon GameStateManager::GameState::BlackWon
#define ChoosingColor GameStateManager::GameState::ChoosingColor
#define InitingColors GameStateManager::GameState::InitingColors
#define RestartGame GameStateManager::GameState::RestartGame
#define Pause GameStateManager::GameState::Pause
#define WhiteBlocked GameStateManager::GameState::WhiteBlocked
#define BlackBlocked GameStateManager::GameState::BlackBlocked

#define	PieceColor	Piece::PieceColor

class LevelManager
{
private:
	Field* GameField;
	RenderWindow* _Win;
	std::vector<Piece*> Pieces;
	PlayerController* _PC;
	GameStateManager* _GSM;
	BotController* _BC;
	GameStartPanel* _GameStartPanel;
	GameOverPanel* _GameOverPanel;
	PausePanel* _PausePanel;

public:
	LevelManager(RenderWindow* RenderWin);
	void InitColors();
	~LevelManager();
	void ReinitGame();

	void RedrawWindow();
	void HandleEvent(Event ev);
	void Update();

private:
	void CreatePieces();
	void DrawPieces();
	
	//Тестовая функция. Меняет расположение фигур в начале
	void TestFunc();
};

