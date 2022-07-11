#include "Camera.h"

void Camera::update()
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, -m_position);
	m_model = glm::rotate(m_model, glm::radians(-m_rotation.x), {1.0f, 0.0f, 0.0f});
	m_model = glm::rotate(m_model, glm::radians(-m_rotation.y), {0.0f, 1.0f, 0.0f});
	m_model = glm::rotate(m_model, glm::radians(-m_rotation.z), {0.0f, 0.0f, 1.0f});
}

glm::vec3 Camera::unProject(const glm::vec2& mousePos, float depth) const
{
	depth = glm::clamp(depth, 0.0f, 1.0f);
	const float x = mousePos.x / (static_cast<float>(m_viewportDimensions.x) * 0.5f) - 1.0f;
	const float y = mousePos.y / (static_cast<float>(m_viewportDimensions.y) * 0.5f) - 1.0f;
	const float z = 2.0f * depth - 1.0f;

	const glm::mat4 inverse = glm::inverse(m_proj * m_view * m_model);
	glm::vec4 pos = inverse * glm::vec4(x, -y, z, 1.0f);

	pos.w = 1.0f / pos.w;
	pos.x *= pos.w;
	pos.y *= pos.w;
	pos.z *= pos.w;

	return {pos.x, pos.y, pos.z};
}

glm::vec3 Camera::forwardVec(const glm::vec2& mousePos) const
{
	return glm::normalize(unProject(mousePos, 1.0f) - unProject(mousePos, 0.0f));
}

void Camera::makePerspective(const float& fov, const float& zNear, const float& zFar)
{
	const float aspect = static_cast<float>(m_viewportDimensions.x) / static_cast<float>(m_viewportDimensions.y);
	setProj(glm::perspective(glm::radians(fov), aspect, zNear, zFar));
}

void Camera::makeLookAt(const glm::vec3& forward, const glm::vec3& up)
{
	setView(glm::lookAt(glm::vec3(0.0f), -forward, up));
}

void Camera::setPosition(const glm::vec3& position)
{
	m_position = position;
	update();
}

void Camera::setRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
	update();
}
