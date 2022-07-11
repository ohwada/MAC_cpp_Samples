#pragma once

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window(const char* title, const glm::uvec2& dimensions);
	virtual ~Window();

public:
	SDL_GLContext createContext() const;

	void run();
	void close();

protected:
	virtual void init() = 0;
	virtual void update(const float& deltaTime) = 0;

protected:
	virtual void onResize(const glm::uvec2& windowDimensions);

public:
	bool isKeyDown(SDL_Keycode keycode);
	bool isKeyPressed(SDL_Keycode keycode);
	bool isKeyReleased(SDL_Keycode keycode);
	bool isMouseButtonDown(uint8_t mouseButton);
	bool isMouseButtonPressed(uint8_t mouseButton);
	bool isMouseButtonReleased(uint8_t mouseButton);
	const glm::vec2& getMousePosition() const;
	glm::vec2 getMouseDelta() const;

private:
	void handleEvents();
	float calcDeltaTime();

public:
	const std::string& getTitle() const { return m_title; }
	void setTitle(const std::string& title);

	const glm::uvec2& getDimensions() const { return m_dimensions; }
	void setDimensions(const glm::uvec2& dimensions);

private:
	SDL_Window* m_sdlWindow = nullptr;
	std::string m_title = "Window";
	glm::uvec2 m_dimensions = {800u, 600u};

	bool m_shouldClose = false;
	uint64_t m_frameCount = 0;

	std::map<SDL_Keycode, bool> m_lastKeyboardState;
	std::map<SDL_Keycode, bool> m_keyboardState;

	std::map<uint8_t, bool> m_lastMouseState;
	std::map<uint8_t, bool> m_mouseState;

	glm::vec2 m_mousePosition = {};
	glm::vec2 m_mousePositionLastFrame = {};
};
