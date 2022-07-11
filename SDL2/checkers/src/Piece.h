#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "PieceTypes.h"
#include "Renderer.h"

class Piece
{
public:
	Piece(PieceType type);
	Piece(const Piece& other);

	virtual ~Piece() = default;

public:
	virtual void update(float deltaTime);
	virtual void render(const Renderer& renderer) const = 0;

	virtual void recalculateMoves(
		const glm::ivec2& coords,
		Piece*** board,
		int boardSize
	);

private:
	void interpolatePosition(float speed);

public:
	const Transform& getTransform() const { return m_transform; }

	void setPosition(const glm::vec3& position)
	{
		m_desiredPosition = position;
		m_transform.position = position;
	}

	void setDesiredPosition(const glm::vec3& position) { m_desiredPosition = position; }

	void setInterpolationSpeed(const float& interSpeed) { m_interSpeed = interSpeed; }

	const PieceType& getType() const { return m_type; }

	const PieceState& getState() const { return m_state; }
	void setState(PieceState state) { m_state = state; }

	void setHeld(const bool& held) { m_isHeld = held; }

	const bool& isMovable() const { return m_isMovable; }
	void setMovable(const bool& movable) { m_isMovable = movable; }

	const bool& isCaptured() const { return m_isCaptured; }
	void setCaptured(const bool& captured) { m_isCaptured = captured; }

	const std::vector<Move>& getViableMoves() const { return m_viableMoves; }
	const int& getCapturesCount() const { return m_capturesCount; }

protected:
	std::vector<Move> m_viableMoves;
	int m_capturesCount = 0;

private:
	Transform m_transform = {};
	glm::vec3 m_desiredPosition = {};

	float m_interSpeed = 1.0f;

	PieceType m_type;
	PieceState m_state = PieceState::Neutral;

	bool m_isHeld = false;
	bool m_isMovable = false;
	bool m_isCaptured = false;
};
