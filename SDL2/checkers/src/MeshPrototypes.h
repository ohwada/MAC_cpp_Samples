#pragma once

// change log
// 2020-06-01 K.OHWADA
// change onstexpr  to const
// static constexpr glm::vec3 pieceColorOffsetDarkCapture 

#include <vector>

#include <glm/glm.hpp>

#include "MeshGenerator.h"
#include "PieceTypes.h"

class MeshPrototypes
{
public:
	MeshPrototypes();

public:
	const std::vector<Triangle>& getTileOdd() const { return m_pTileOdd; }
	const std::vector<Triangle>& getTileEven() const { return m_pTileEven; }

	// TODO:: PieceFactory?
	const std::vector<Triangle>& getPiece(PieceType type, PieceState state) const;
	const std::vector<Triangle>& getPieceLight(PieceState state) const;
	const std::vector<Triangle>& getPieceDark(PieceState state) const;

	const std::vector<Triangle>& getPieceLightNeutral() const { return m_pPieceLightNeutral; }
	const std::vector<Triangle>& getPieceLightMovable() const { return m_pPieceLightMovable; }
	const std::vector<Triangle>& getPieceLightSelected() const { return m_pPieceLightSelected; }
	const std::vector<Triangle>& getPieceLightCapture() const { return m_pPieceLightCapture; }

	const std::vector<Triangle>& getPieceDarkNeutral() const { return m_pPieceDarkNeutral; }
	const std::vector<Triangle>& getPieceDarkMovable() const { return m_pPieceDarkMovable; }
	const std::vector<Triangle>& getPieceDarkSelected() const { return m_pPieceDarkSelected; }
	const std::vector<Triangle>& getPieceDarkCapture() const { return m_pPieceDarkCapture; }

protected:
	// static constexpr glm::vec3 tableTileColorOdd = {0.85f, 0.75f, 0.5f};
	const glm::vec3 tableTileColorOdd{0.85f, 0.75f, 0.5f};

	// static constexpr glm::vec3 tableTileColorEven = {0.29f, 0.24f, 0.21f};
	const glm::vec3 tableTileColorEven{0.29f, 0.24f, 0.21f};

	// static constexpr glm::vec3 pieceColorLightNeutral = {0.9f, 0.9f, 0.9f};
	const glm::vec3 pieceColorLightNeutral{0.9f, 0.9f, 0.9f};

	// static constexpr glm::vec3 pieceColorOffsetLightMovable = {-0.15f, -0.15f, 0.1f};
	const glm::vec3 pieceColorOffsetLightMovable{-0.15f, -0.15f, 0.1f};

	//static constexpr glm::vec3 pieceColorOffsetLightSelected = {0.1f, 0.1f, 0.1f};
	const glm::vec3 pieceColorOffsetLightSelected{0.1f, 0.1f, 0.1f};

	// static constexpr glm::vec3 pieceColorOffsetLightCapture = {0.1f, -0.45f, -0.4f};
	const glm::vec3 pieceColorOffsetLightCapture{0.1f, -0.45f, -0.4f};

	// static constexpr glm::vec3 pieceColorDarkNeutral = {0.2f, 0.2f, 0.2f};
	const glm::vec3 pieceColorDarkNeutral {0.2f, 0.2f, 0.2f};

	// static constexpr glm::vec3 pieceColorOffsetDarkMovable = {-0.02f, -0.02f, 0.23f};
	const glm::vec3 pieceColorOffsetDarkMovable{-0.02f, -0.02f, 0.23f};

	// static constexpr glm::vec3 pieceColorOffsetDarkSelected = {0.15f, 0.15f, 0.15f};
	const glm::vec3 pieceColorOffsetDarkSelected{0.15f, 0.15f, 0.15f};

	// static constexpr glm::vec3 pieceColorOffsetDarkCapture = {0.23f, -0.02f, -0.02f};
	const glm::vec3 pieceColorOffsetDarkCapture{0.23f, -0.02f, -0.02f};

private:
	MeshGenerator m_generator;

	std::vector<Triangle> m_pTileOdd;
	std::vector<Triangle> m_pTileEven;

	std::vector<Triangle> m_pPieceLightNeutral;
	std::vector<Triangle> m_pPieceLightMovable;
	std::vector<Triangle> m_pPieceLightSelected;
	std::vector<Triangle> m_pPieceLightCapture;

	std::vector<Triangle> m_pPieceDarkNeutral;
	std::vector<Triangle> m_pPieceDarkMovable;
	std::vector<Triangle> m_pPieceDarkSelected;
	std::vector<Triangle> m_pPieceDarkCapture;
};
