#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera() = default;

public:
	void update();

	glm::vec3 unProject(const glm::vec2& mousePos, float depth = 0.0f) const;
	glm::vec3 forwardVec(const glm::vec2& mousePos) const;

	void makePerspective(const float& fov, const float& zNear, const float& zFar);
	void makeLookAt(const glm::vec3& forward, const glm::vec3& up);

public:
	const glm::uvec2& getViewportDimensions() const { return m_viewportDimensions; }
	void setViewportDimensions(const glm::uvec2 viewportDimensions) { m_viewportDimensions = viewportDimensions; }

	const glm::vec3& getPosition() const { return m_position; }
	void setPosition(const glm::vec3& position);

	const glm::vec3& getRotation() const { return m_rotation; }
	void setRotation(const glm::vec3& rotation);

	const glm::mat4& getModel() const { return m_model; }
	void setModel(const glm::mat4& model) { m_model = model; }

	const glm::mat4& getView() const { return m_view; }
	void setView(const glm::mat4& view) { m_view = view; }

	const glm::mat4& getProj() const { return m_proj; }
	void setProj(const glm::mat4& proj) { m_proj = proj; }

	glm::mat4 getModelView() const { return m_view * m_model; }


private:
	glm::uvec2 m_viewportDimensions{0.0f, 0.0f};
	glm::vec3 m_position{0.0f, 0.0f, 0.0f};
	glm::vec3 m_rotation{0.0f, 0.0f, 0.0f};

	glm::mat4 m_model{glm::mat4(1.0f)};
	glm::mat4 m_view{glm::mat4(1.0f)};
	glm::mat4 m_proj{glm::mat4(1.0f)};
};
