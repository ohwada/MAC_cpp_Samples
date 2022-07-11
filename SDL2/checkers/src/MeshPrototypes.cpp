#include "MeshPrototypes.h"

MeshPrototypes::MeshPrototypes()
{
	m_generator.setColor(tableTileColorOdd);
	m_pTileOdd = m_generator.makeQuad(1.0f, 1.0f);

	m_generator.setColor(tableTileColorEven);
	m_pTileEven = m_generator.makeQuad(1.0f, 1.0f);

	m_generator.setColor(pieceColorLightNeutral);
	m_pPieceLightNeutral = m_generator.makeCylinder(0.35f, 0.2f);
	m_pPieceLightMovable = m_pPieceLightNeutral;
	for (auto& tri : m_pPieceLightMovable)
	{
		tri.v1.color += pieceColorOffsetLightMovable;
		tri.v2.color += pieceColorOffsetLightMovable;
		tri.v3.color += pieceColorOffsetLightMovable;
	}
	m_pPieceLightSelected = m_pPieceLightNeutral;
	for (auto& tri : m_pPieceLightSelected)
	{
		tri.v1.color += pieceColorOffsetLightSelected;
		tri.v2.color += pieceColorOffsetLightSelected;
		tri.v3.color += pieceColorOffsetLightSelected;
	}
	m_pPieceLightCapture = m_pPieceLightNeutral;
	for (auto& tri : m_pPieceLightCapture)
	{
		tri.v1.color += pieceColorOffsetLightCapture;
		tri.v2.color += pieceColorOffsetLightCapture;
		tri.v3.color += pieceColorOffsetLightCapture;
	}


	m_generator.setColor(pieceColorDarkNeutral);
	m_pPieceDarkNeutral = m_generator.makeCylinder(0.35f, 0.2f);
	m_pPieceDarkMovable = m_pPieceDarkNeutral;
	for (auto& tri : m_pPieceDarkMovable)
	{
		tri.v1.color += pieceColorOffsetDarkMovable;
		tri.v2.color += pieceColorOffsetDarkMovable;
		tri.v3.color += pieceColorOffsetDarkMovable;
	}
	m_pPieceDarkSelected = m_pPieceDarkNeutral;
	for (auto& tri : m_pPieceDarkSelected)
	{
		tri.v1.color += pieceColorOffsetDarkSelected;
		tri.v2.color += pieceColorOffsetDarkSelected;
		tri.v3.color += pieceColorOffsetDarkSelected;
	}
	m_pPieceDarkCapture = m_pPieceDarkNeutral;
	for (auto& tri : m_pPieceDarkCapture)
	{
		tri.v1.color += pieceColorOffsetDarkCapture;
		tri.v2.color += pieceColorOffsetDarkCapture;
		tri.v3.color += pieceColorOffsetDarkCapture;
	}
}

const std::vector<Triangle>& MeshPrototypes::getPiece(PieceType type, PieceState state) const
{
	return type == PieceType::Light ? getPieceLight(state) : getPieceDark(state);
}

const std::vector<Triangle>& MeshPrototypes::getPieceLight(PieceState state) const
{
	switch (state)
	{
	case PieceState::Neutral:
		return getPieceLightNeutral();
	case PieceState::Movable:
		return getPieceLightMovable();
	case PieceState::Selected:
		return getPieceLightSelected();
	case PieceState::Capture:
		return getPieceLightCapture();
	}
	return getPieceLightNeutral();
}

const std::vector<Triangle>& MeshPrototypes::getPieceDark(PieceState state) const
{
	switch (state)
	{
	case PieceState::Neutral:
		return getPieceDarkNeutral();
	case PieceState::Movable:
		return getPieceDarkMovable();
	case PieceState::Selected:
		return getPieceDarkSelected();
	case PieceState::Capture:
		return getPieceDarkCapture();
	}
	return getPieceDarkNeutral();
}
