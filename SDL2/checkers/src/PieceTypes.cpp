#include "PieceTypes.h"

bool Move::operator==(const glm::ivec2& vec2) const
{
	return vec2 == destination;
}

const Selection Selection::NONE = {nullptr, {-1.0f, -1.0f}};

bool Selection::hasPiece() const
{
	return piece != nullptr;
}

bool Selection::operator==(const Selection& other) const
{
	return piece == other.piece && coords == other.coords;
}

bool Selection::operator !=(const Selection& other) const
{
	return !(*this == other);
}
