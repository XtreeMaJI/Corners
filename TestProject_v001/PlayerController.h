#pragma once
#include "Piece.h"
#include "GameStateManager.h"

#define WhiteTurn GameStateManager::GameState::WhiteTurn
#define BlackTurn GameStateManager::GameState::BlackTurn

class PlayerController
{
private:
	std::vector<Piece*> _PlayerPieces;
	Piece* SelectedPiece = nullptr;
	
	sf::Sprite PieceSelection;

	GameStateManager* _GSM;

public:
	Piece::PieceColor Color; //Цвет фигур игрока

public:
	PlayerController(Piece::PieceColor newColor, std::vector<Piece*>* allPieces, GameStateManager* newGSM);
	~PlayerController();
	void HandleMouseButtonPress(sf::Vector2i MousePos);
private:
	void SelectPiece(Piece * newSelectedPiece);
	void DropSelection();
};

