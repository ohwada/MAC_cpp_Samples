#include "GameWindow.h"

#include "Checkers.h"

GameWindow::GameWindow(const char* title, const glm::uvec2& dimensions)
	: Window(title, dimensions),
	  m_renderer(this)
{
	m_game = new Checkers(this, 10);
}

GameWindow::~GameWindow()
{
	delete m_game;
}

void GameWindow::init()
{
	const glm::uvec2& windowDimensions = getDimensions();
	m_camera.setViewportDimensions({windowDimensions.x, windowDimensions.y});
	m_camera.makePerspective(45.0f, 1.0f, 1000.0f);
	m_camera.makeLookAt({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
	m_camera.setPosition({0.0f, -1.0f, 11.0f});
	m_camera.setRotation({-45.0f, 0.0f, 0.0f});

	const LightSource light = {{0.3f, -1.0f, 0.45f}, 1.0f};

	m_renderer.setClearColor({0.15f, 0.15f, 0.15f});
	m_renderer.setLightSource(light);
	m_renderer.setAmbientLight({0.4f, 0.4f, 0.4f});

	m_game->reset();
}

void GameWindow::update(const float& deltaTime)
{
	m_elapsed = m_elapsed + deltaTime;

	const LightSource light = {
		{glm::cos(m_elapsed) * 0.3f, -1.0f, glm::sin(m_elapsed) * 0.45f},
		1.0f
	};
	m_renderer.setLightSource(light);

	m_game->update(deltaTime);

	m_renderer.beginFrame(&m_camera);
	m_game->render(m_renderer);
}

void GameWindow::onResize(const glm::uvec2& windowDimensions)
{
	Window::onResize(windowDimensions);
	m_camera.setViewportDimensions({windowDimensions.x, windowDimensions.y});
	m_camera.makePerspective(45.0f, 1.0f, 1000.0f);
	m_camera.makeLookAt({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
}
