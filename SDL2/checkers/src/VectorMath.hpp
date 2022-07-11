#pragma once

#include <algorithm>
#include <glm/glm.hpp>

class VectorMath
{
private:
	VectorMath() = default;

public:
	static glm::vec3 linePlaneIntersect(
		const glm::vec3& rayVec,
		const glm::vec3& rayPoint,
		const glm::vec3& planeNormal,
		const glm::vec3& planePoint
	)
	{
		const glm::vec3 diff = rayPoint - planePoint;
		const float prod1 = glm::dot(diff, planeNormal);
		const float prod2 = glm::dot(rayVec, planeNormal);
		const float prod3 = prod1 / prod2;
		return rayPoint - rayVec * prod3;
	}

	static glm::vec3 rotate(
		const glm::vec3& vector,
		const glm::vec3& rotation
	)
	{
		glm::mat4 rotationMat = glm::mat4(1.0f);
		rotationMat = glm::rotate(
			rotationMat,
			glm::radians(rotation.x),
			{1.0f, 0.0f, 0.0f}
		);
		rotationMat = glm::rotate(
			rotationMat,
			glm::radians(rotation.y),
			{0.0f, 1.0f, 0.0f}
		);
		rotationMat = glm::rotate(
			rotationMat,
			glm::radians(rotation.z),
			{0.0f, 0.0f, 1.0f}
		);
		return rotationMat * glm::vec4{vector.x, vector.y, vector.z, 0.0f};
	}
};
