#include "Renderer.h"

#include <SDL2/SDL_opengl.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(const Window* const window)
{
	m_glContext = window->createContext();
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(m_glContext);
}

void Renderer::beginFrame(const Camera* const camera) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(camera->getProj()));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(camera->getModelView()));
}

void Renderer::drawTriangles(
	const std::vector<Triangle>& triangles,
	const Transform& transform
) const
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(
		model,
		glm::radians(transform.rotation.x),
		{1.0f, 0.0f, 0.0f}
	);
	model = glm::rotate(
		model,
		glm::radians(transform.rotation.y),
		{0.0f, 1.0f, 0.0f}
	);
	model = glm::rotate(
		model,
		glm::radians(transform.rotation.z),
		{0.0f, 0.0f, 1.0f}
	);
	model = glm::scale(model, transform.scale);

	glm::mat4 normal = glm::mat4(1.0f);
	normal = glm::rotate(
		normal,
		glm::radians(transform.rotation.x),
		{1.0f, 0.0f, 0.0f}
	);
	normal = glm::rotate(
		normal,
		glm::radians(transform.rotation.y),
		{0.0f, 1.0f, 0.0f}
	);
	normal = glm::rotate(
		normal,
		glm::radians(transform.rotation.z),
		{0.0f, 0.0f, 1.0f}
	);

	for (const auto& triangle : triangles)
	{
		drawTriangle(triangle, model, normal);
	}
}

void Renderer::drawTriangle(
	const Triangle& triangle,
	const glm::mat4& modelMat,
	const glm::mat4& normalMat
) const
{
	glBegin(GL_TRIANGLES);

	drawVertex(triangle.v1, modelMat, normalMat);
	drawVertex(triangle.v2, modelMat, normalMat);
	drawVertex(triangle.v3, modelMat, normalMat);

	glEnd();
}

void Renderer::drawVertex(
	const Vertex& vertex,
	const glm::mat4& modelMat,
	const glm::mat4& normalMat
) const
{
	glm::vec4 position = {
		vertex.position.x,
		vertex.position.y,
		vertex.position.z,
		1.0f
	};
	glm::vec4 normal = {
		vertex.normal.x,
		vertex.normal.y,
		vertex.normal.z,
		1.0f
	};
	position = modelMat * position;
	normal = normalMat * normal;

	const glm::vec3 normalized = glm::normalize(glm::vec3(normal.x, normal.y, normal.z));
	const float dot = glm::dot(normalized, -m_lightSource.direction);
	const float intensity = glm::max(0.0f, dot) * m_lightSource.intensity;
	glm::vec3 multi = {intensity, intensity, intensity};
	multi.x = glm::clamp(multi.x + m_ambientLight.x, 0.0f, 1.0f);
	multi.y = glm::clamp(multi.y + m_ambientLight.y, 0.0f, 1.0f);
	multi.z = glm::clamp(multi.z + m_ambientLight.z, 0.0f, 1.0f);
	const glm::vec3 color = vertex.color * multi;

	glColor3f(color.r, color.g, color.b);
	glVertex3f(position.x, position.y, position.z);
}

void Renderer::setClearColor(const glm::vec3 clearColor)
{
	m_clearColor = clearColor;
	glClearColor(
		m_clearColor.r,
		m_clearColor.g,
		m_clearColor.b,
		1.0f
	);
}

void Renderer::setLightSource(const LightSource& lightSource)
{
	m_lightSource = lightSource;
	m_lightSource.direction = glm::normalize(m_lightSource.direction);
	m_lightSource.intensity = glm::clamp(m_lightSource.intensity, 0.0f, 1.0f);
}
