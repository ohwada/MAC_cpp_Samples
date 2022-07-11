#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "RenderTypes.h"

class MeshGenerator
{
public:
	MeshGenerator() = default;

public:
	std::vector<Triangle> makeQuad(const float& width, const float& height) const;
	std::vector<Triangle> makeCylinder(const float& radius, const float& height) const;
	std::vector<Triangle> makeDonut(const float& R, const float& r) const;

public:
	void setColor(const glm::vec3& color) { m_color = color; }

private:
	glm::vec3 m_color = glm::vec3(1.0f);
};
