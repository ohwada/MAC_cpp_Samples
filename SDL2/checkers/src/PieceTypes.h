#pragma once

#include <glm/glm.hpp>

enum PieceType
{
	Light,
	Dark
};

enum PieceState
{
	Neutral,
	Movable,
	Selected,
	Capture
};

struct Move
{
	glm::ivec2 destination = {};
	glm::ivec2 capture = {};
	bool captures = false;

	bool operator==(const glm::ivec2& vec2) const;
};

struct Selection
{
	class Piece* piece;
	glm::ivec2 coords;

	static const Selection NONE;

	bool hasPiece() const;

	bool operator==(const Selection& other) const;
	bool operator !=(const Selection& other) const;
};
