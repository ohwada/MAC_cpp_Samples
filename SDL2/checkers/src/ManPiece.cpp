#include "ManPiece.h"

#include <algorithm>

ManPiece::ManPiece(PieceType type) : Piece(type)
{
}

ManPiece::ManPiece(const Piece& other) : Piece(other)
{
}

void ManPiece::update(float deltaTime)
{
	Piece::update(deltaTime);
}

void ManPiece::render(const Renderer& renderer) const
{
	const std::vector<Triangle> mesh = renderer.getMeshPrototypes()
	                                           .getPiece(getType(), getState());

	renderer.drawTriangles(mesh, getTransform());
}

void ManPiece::recalculateMoves(
	const glm::ivec2& coords,
	Piece*** board,
	int boardSize
)
{
	Piece::recalculateMoves(coords, board, boardSize);
	const int forward = getType() == PieceType::Light ? -1 : 1;

	calculateMovesDiagonal(coords, board, boardSize, forward, 1, 1);
	calculateMovesDiagonal(coords, board, boardSize, forward, -1, 1);

	calculateCapturesDiagonal(coords, board, boardSize, forward, 1, 1);
	calculateCapturesDiagonal(coords, board, boardSize, forward, -1, 1);
	calculateCapturesDiagonal(coords, board, boardSize, -forward, 1, 1);
	calculateCapturesDiagonal(coords, board, boardSize, -forward, -1, 1);

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

void ManPiece::calculateMovesDiagonal(
	const glm::ivec2& coords,
	Piece*** board,
	int boardSize,
	int yStep,
	int xStep,
	int limit
)
{
	int check = 0;
	glm::ivec2 checkCoords = coords;
	while (check < limit
		&& checkCoords.x + yStep >= 0
		&& checkCoords.x + yStep < boardSize
		&& checkCoords.y + xStep >= 0
		&& checkCoords.y + xStep < boardSize)
	{
		checkCoords.x += yStep;
		checkCoords.y += xStep;
		if (board[checkCoords.x][checkCoords.y] == nullptr)
		{
			//  m_viableMoves.push_back({
				// checkCoords,
				// {},
				// false
			//});
			Move move;
			move. destination = checkCoords;
			m_viableMoves.push_back(move);
		}
		else
		{
			break;
		}
		check++;
	}
}

void ManPiece::calculateCapturesDiagonal(
	const glm::ivec2& coords,
	Piece*** board,
	int boardSize,
	int yStep,
	int xStep,
	int limit
)
{
	int check = 0;
	glm::ivec2 checkCoords = coords;
	while (check < limit
		&& checkCoords.x + yStep >= 0
		&& checkCoords.x + yStep < boardSize
		&& checkCoords.y + xStep >= 0
		&& checkCoords.y + xStep < boardSize)
	{
		checkCoords.x += yStep;
		checkCoords.y += xStep;
		if (board[checkCoords.x][checkCoords.y] != nullptr)
		{
			if (board[checkCoords.x][checkCoords.y]->getType() != getType()
				&& !board[checkCoords.x][checkCoords.y]->isCaptured()
				&& checkCoords.x + yStep >= 0 && checkCoords.x + yStep < boardSize
				&& checkCoords.y + xStep >= 0 && checkCoords.y + xStep < boardSize
				&& board[checkCoords.x + yStep][checkCoords.y + xStep] == nullptr)
			{
				++m_capturesCount;
				const glm::ivec2 moveCoords = {
					checkCoords.x + yStep,
					checkCoords.y + xStep
				};

				///m_viableMoves.push_back({
					//moveCoords,
					//checkCoords,
					//true
				//});

				Move move;
				move.destination = moveCoords;
				move.capture = checkCoords;
				move.captures = true;
				m_viableMoves.push_back(move);
		
			}
			break;
		}
		check++;
	}
}
