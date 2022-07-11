// chnge log
// 2022-06-01 K.OHWADA
// 	constexpr float step = glm::pi<float>() / 10.0f;

#include "MeshGenerator.h"

#include <glm/ext/scalar_constants.hpp>

std::vector<Triangle> MeshGenerator::makeQuad(const float& width, const float& height) const
{
	std::vector<Triangle> triangles;
	const float halfWidth = width / 2.0f;
	const float halfHeight = height / 2.0f;

	Vertex vertices[4];

	for (auto& vertex : vertices)
	{
		vertex.color = m_color;
		vertex.normal = {0.0f, 1.0f, 0.0f};
	}

	vertices[0].position = {-halfWidth, 0.0f, -halfHeight};
	vertices[1].position = {halfWidth, 0.0f, -halfHeight};
	vertices[2].position = {halfWidth, 0.0f, halfHeight};
	vertices[3].position = {-halfWidth, 0.0f, halfHeight};

	triangles.push_back({vertices[0], vertices[1], vertices[2]});
	triangles.push_back({vertices[0], vertices[2], vertices[3]});

	return triangles;
}

std::vector<Triangle> MeshGenerator::makeCylinder(const float& radius, const float& height) const
{
	std::vector<Triangle> triangles;

	// constexpr float step = glm::pi<float>() / 10.0f;
	const float step = glm::pi<float>() / 10.0f;

	const float h = height / 2.0f;

	for (float i = 0.0; i < glm::pi<float>() * 2.0f; i += step)
	{
		const float x = glm::sin(i);
		const float y = glm::cos(i);

		const float xN = glm::sin(i + step);
		const float yN = glm::cos(i + step);

		Vertex vertices[10];

		for (auto& vertex : vertices)
		{
			vertex.color = m_color;
		}

		// TOP
		vertices[0].position = {0.0f, h, 0.0f};
		vertices[1].position = {x * radius, h, y * radius};
		vertices[2].position = {xN * radius, h, yN * radius};

		vertices[0].normal = {0.0f, 1.0f, 0.0f};
		vertices[1].normal = {0.0f, 1.0f, 0.0f};
		vertices[2].normal = {0.0f, 1.0f, 0.0f};

		triangles.push_back({vertices[0], vertices[1], vertices[2]});

		// SIDE
		vertices[3].position = {x * radius, h, y * radius};
		vertices[4].position = {x * radius, -h, y * radius};
		vertices[5].position = {xN * radius, -h, yN * radius};
		vertices[6].position = {xN * radius, h, yN * radius};

		vertices[3].normal = {x * radius, 0.0f, y * radius};
		vertices[4].normal = {x * radius, 0.0f, y * radius};
		vertices[5].normal = {xN * radius, 0.0f, yN * radius};
		vertices[6].normal = {xN * radius, 0.0f, yN * radius};

		triangles.push_back({vertices[3], vertices[4], vertices[6]});
		triangles.push_back({vertices[4], vertices[5], vertices[6]});


		// BOTTOM
		vertices[7].position = {0.0f, -h, 0.0f};
		vertices[8].position = {x * radius, -h, y * radius};
		vertices[9].position = {xN * radius, -h, yN * radius};

		vertices[7].normal = {0.0f, -1.0f, 0.0f};
		vertices[8].normal = {0.0f, -1.0f, 0.0f};
		vertices[9].normal = {0.0f, -1.0f, 0.0f};

		triangles.push_back({vertices[7], vertices[8], vertices[9]});
	}
	return triangles;
}

std::vector<Triangle> MeshGenerator::makeDonut(const float& R, const float& r) const
{
	std::vector<Triangle> triangles;

	// constexpr float step = glm::pi<float>() / 10.0f;
	const float step = glm::pi<float>() / 10.0f;

	for (float i = 0.0; i < glm::pi<float>() * 2.0f; i += step)
	{
		for (float j = 0.0; j < glm::pi<float>() * 2.0f; j += step)
		{
			const float Rx = R * glm::sin(i);
			const float Ry = R * glm::cos(i);

			const float x = Rx + r * glm::cos(j) * glm::sin(i);
			const float y = Ry + r * glm::cos(j) * glm::cos(i);
			const float z = r * glm::sin(j);

			const float xN = Rx + r * glm::cos(j + step) * glm::sin(i);
			const float yN = Ry + r * glm::cos(j + step) * glm::cos(i);
			const float zN = r * glm::sin(j + step);

			const float R_x = R * glm::sin(i + step);
			const float R_y = R * glm::cos(i + step);

			const float _x = R_x + r * glm::cos(j) * glm::sin(i + step);
			const float _y = R_y + r * glm::cos(j) * glm::cos(i + step);
			const float _z = r * glm::sin(j);

			const float _xN = R_x + r * glm::cos(j + step) * glm::sin(i + step);
			const float _yN = R_y + r * glm::cos(j + step) * glm::cos(i + step);
			const float _zN = r * glm::sin(j + step);

			Vertex vertices[4];
			for (auto& vertex : vertices)
			{
				vertex.color = m_color;
			}
			vertices[0].position = {x, y, z};
			vertices[1].position = {xN, yN, zN};
			vertices[2].position = {_x, _y, _z};
			vertices[3].position = {_xN, _yN, _zN};

			vertices[0].normal = {
				glm::cos(j) * glm::sin(i),
				glm::cos(j) * glm::cos(i),
				glm::sin(j)
			};
			vertices[1].normal = {
				glm::cos(j + step) * glm::sin(i),
				glm::cos(j + step) * glm::cos(i),
				glm::sin(j + step)
			};
			vertices[2].normal = {
				glm::cos(j) * glm::sin(i + step),
				glm::cos(j) * glm::cos(i + step),
				glm::sin(j)
			};
			vertices[3].normal = {
				glm::cos(j + step) * glm::sin(i + step),
				glm::cos(j + step) * glm::cos(i + step),
				glm::sin(j + step)
			};

			triangles.push_back({vertices[0], vertices[1], vertices[2]});
			triangles.push_back({vertices[2], vertices[1], vertices[3]});
		}
	}
	return triangles;
}
