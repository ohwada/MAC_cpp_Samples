#include "Piece.h"

Piece::Piece(PieceType type) : m_type(type)
{
}

Piece::Piece(const Piece& other)
{
	m_viableMoves = other.m_viableMoves;
	m_capturesCount = other.m_capturesCount;
	m_transform = other.m_transform;
	m_desiredPosition = other.m_desiredPosition;
	m_interSpeed = other.m_interSpeed;
	m_type = other.m_type;
	m_state = other.m_state;
	m_isHeld = other.m_isHeld;
	m_isMovable = other.m_isMovable;
	m_isCaptured = other.m_isCaptured;
}

void Piece::update(float deltaTime)
{
	interpolatePosition(m_interSpeed * deltaTime);
}

void Piece::recalculateMoves(
	const glm::ivec2& coords,
	Piece*** board,
	int boardSize
)
{
	m_viableMoves.clear();
	m_capturesCount = 0;
}

void Piece::interpolatePosition(float speed)
{
	const glm::vec3 movementVector = m_desiredPosition - m_transform.position;
	const float movementVectorLength = glm::length(movementVector);
	glm::vec3 desiredMovementVector = glm::normalize(movementVector) * speed;
	desiredMovementVector += desiredMovementVector * movementVectorLength;
	const float desiredMovementVectorLength = glm::length(desiredMovementVector);
	if (desiredMovementVectorLength < movementVectorLength)
	{
		m_transform.position += desiredMovementVector;
	}
	else
	{
		m_transform.position = m_desiredPosition;
	}

	if (m_isHeld)
	{
		m_transform.rotation = {movementVector.z * 100.0f, 0.0f, -movementVector.x * 100.0f};
		m_transform.rotation.x = glm::clamp(m_transform.rotation.x, -60.0f, 60.0f);
		m_transform.rotation.z = glm::clamp(m_transform.rotation.z, -60.0f, 60.0f);
	}
	else
	{
		m_transform.rotation = {0.0f, 0.0f, 0.0f};
	}
}
