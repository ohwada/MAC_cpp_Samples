#pragma once

#include "ManPiece.h"

class KingPiece : public ManPiece
{
public:
	KingPiece(PieceType type);
	KingPiece(const Piece& other);

	virtual ~KingPiece() override = default;

public:
	virtual void update(float deltaTime) override;
	virtual void render(const Renderer& renderer) const override;

	virtual void recalculateMoves(
		const glm::ivec2& coords,
		Piece*** board,
		int boardSize
	) override;
};
