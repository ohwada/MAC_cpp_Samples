#pragma once

#include <functional>

#include "GameWindow.h"
#include "Piece.h"
#include "VectorMath.hpp"

class GameWindow;

struct Player
{
	PieceType pieceType = PieceType::Light;
	bool capturedThisTurn = false;
	glm::ivec2 capturingPieceCoords = {0, 0};
};

enum GameState
{
	TitleScreen,
	PlayerMoving,
	ChangingPlayer,
	GameOver
};

class Checkers
{
public:
	Checkers(GameWindow* window, uint8_t boardSize);
	virtual ~Checkers();

public:
	void reset();
	void update(const float& deltaTime);
	void render(const Renderer& renderer) const;

	void forEachPiece(const std::function<void(Piece*, int, int)>& func) const;

protected:
	void updateStatePlayerMoving(const float& deltaTime);
	void updateStateChangingPlayer(const float& deltaTime);
	void updateStateGameOver(const float& deltaTime);

	void updateHeldPosition() const;
	void updateSelection();
	void updateBoardState() const;
	void updatePieceStates() const;

	void pickUpPiece();
	void putBackPiece();
	void makeMove(const Move& move);
	void checkForPieceUpgrade(int z, int x) const;
	void finishMove();
	void checkForGameOver();

protected:
	void drawMoves(const Renderer& renderer) const;
	void drawTable(const Renderer& renderer) const;
	void drawTitle(const Renderer& renderer) const;
	void drawGameOver(const Renderer& renderer) const;

protected:
	static bool isDarkTile(int x, int z);
	glm::vec3 positionFromBoardCoords(int x, int z) const;
	bool isInBoardBounds(const glm::ivec2& position) const;

	std::vector<glm::ivec2> getMovablePieces() const;
	bool hasCaptures() const;

	bool animateCamera(const float& deltaTime) const;

private:
	GameWindow* m_window = nullptr;
	uint8_t m_boardSize = 10;

	Piece*** m_board;
	GameState m_state = GameState::TitleScreen;
	Player m_currentPlayer = {};

	Selection m_selected = Selection::NONE;
	Selection m_held = Selection::NONE;

	float** m_gameOverJumpVelocity;

private:
	static constexpr int gameOverText[9][15] = {
		{1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
		{1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0},
		{1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1}
	};

	static constexpr int titleText[4][31] = {
		{1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
		{1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0}
	};
};
