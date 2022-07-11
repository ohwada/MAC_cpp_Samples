#include "KingPiece.h"

#include "VectorMath.hpp"

KingPiece::KingPiece(PieceType type) : ManPiece(type)
{
}

KingPiece::KingPiece(const Piece& other) : ManPiece(other)
{
}

void KingPiece::update(float deltaTime)
{
	ManPiece::update(deltaTime);
}

void KingPiece::render(const Renderer& renderer) const
{
	ManPiece::render(renderer);
	const std::vector<Triangle> mesh = renderer.getMeshPrototypes()
	                                           .getPiece(getType(), getState());

	Transform transform = getTransform();
	const glm::vec3 up = VectorMath::rotate(
		{0.0f, 1.0f, 0.0f},
		transform.rotation
	);
	const glm::vec3 pieceUp = glm::normalize(up) * 0.2f;
	transform.position += pieceUp;
	renderer.drawTriangles(mesh, transform);
}

void KingPiece::recalculateMoves(
	const glm::ivec2& coords,
	Piece*** board,
	int boardSize
)
{
	Piece::recalculateMoves(coords, board, boardSize);
	const int forward = getType() == PieceType::Light ? -1 : 1;

	calculateMovesDiagonal(coords, board, boardSize, forward, 1, 99);
	calculateMovesDiagonal(coords, board, boardSize, forward, -1, 99);
	calculateMovesDiagonal(coords, board, boardSize, -forward, 1, 99);
	calculateMovesDiagonal(coords, board, boardSize, -forward, -1, 99);

	calculateCapturesDiagonal(coords, board, boardSize, forward, 1, 99);
	calculateCapturesDiagonal(coords, board, boardSize, forward, -1, 99);
	calculateCapturesDiagonal(coords, board, boardSize, -forward, 1, 99);
	calculateCapturesDiagonal(coords, board, boardSize, -forward, -1, 99);

	if (getCapturesCount() > 0)
	{
		m_viableMoves.erase(
			std::remove_if(
				m_viableMoves.begin(),
				m_viableMoves.end(),
				[](const Move& move) -> bool
				{
					return !move.captures;
				}),
			m_viableMoves.end()
		);
	}
}
