#pragma once

#include "Piece.h"

class ManPiece : public Piece
{
public:
	ManPiece(PieceType type);
	ManPiece(const Piece& other);

	virtual ~ManPiece() override = default;

public:
	virtual void update(float deltaTime) override;
	virtual void render(const Renderer& renderer) const override;

	virtual void recalculateMoves(
		const glm::ivec2& coords,
		Piece*** board,
		int boardSize
	) override;

protected:
	void calculateMovesDiagonal(
		const glm::ivec2& coords,
		Piece*** board,
		int boardSize,
		int yStep,
		int xStep,
		int limit
	);
	void calculateCapturesDiagonal(
		const glm::ivec2& coords,
		Piece*** board,
		int boardSize,
		int yStep,
		int xStep,
		int limit
	);
};
