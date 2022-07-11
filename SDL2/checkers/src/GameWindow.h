#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "MeshPrototypes.h"

class Checkers;

class GameWindow : public Window
{
public:
	GameWindow(const char* title, const glm::uvec2& dimensions);
	~GameWindow() override;

protected:
	void init() override;
	void update(const float& deltaTime) override;
	void onResize(const glm::uvec2& windowDimensions) override;

public:
	const float& getElapsedTime() const { return m_elapsed; }
	const Camera& getCamera() const { return m_camera; }
	void setCamera(const Camera& camera) { m_camera = camera; }
	const MeshPrototypes& getPrototypes() const { return m_prototypes; }

private:
	Renderer m_renderer;
	Camera m_camera;

	float m_elapsed = 0.0;

	MeshPrototypes m_prototypes;

	Checkers* m_game;
};
