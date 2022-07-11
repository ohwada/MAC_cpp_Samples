#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Window.h"
#include "Camera.h"
#include "RenderTypes.h"
#include "MeshPrototypes.h"

class Renderer
{
public:
	explicit Renderer(const Window* const window);
	~Renderer();

public:
	void beginFrame(const Camera* const camera) const;

	void drawTriangles(
		const std::vector<Triangle>& triangles,
		const Transform& transform = {}
	) const;
	void drawTriangle(
		const Triangle& triangle,
		const glm::mat4& modelMat = glm::mat4(1.0f),
		const glm::mat4& normalMat = glm::mat4(1.0f)
	) const;
	void drawVertex(
		const Vertex& vertex,
		const glm::mat4& modelMat = glm::mat4(1.0f),
		const glm::mat4& normalMat = glm::mat4(1.0f)
	) const;

public:
	void setClearColor(const glm::vec3 clearColor);

	const LightSource& getLightSource() const { return m_lightSource; }
	void setLightSource(const LightSource& lightSource);

	const glm::vec3& getAmbientLight() const { return m_ambientLight; }
	void setAmbientLight(const glm::vec3& ambientLight) { m_ambientLight = ambientLight; }

	const MeshPrototypes& getMeshPrototypes() const { return m_prototypes; }

private:
	SDL_GLContext m_glContext;

	glm::vec3 m_clearColor = {0.0f, 0.0f, 0.0f};
	LightSource m_lightSource = {{0.0f, -1.0f, 0.0f}, 1.0f};
	glm::vec3 m_ambientLight = {0.0f, 0.0f, 0.0f};

	MeshPrototypes m_prototypes;
};
