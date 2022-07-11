#include "Window.h"

#include <SDL2/SDL_opengl.h>

Window::Window(const char* title, const glm::uvec2& dimensions)
	: m_title(title),
	  m_dimensions(dimensions)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_sdlWindow = SDL_CreateWindow(
		m_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(m_dimensions.x),
		static_cast<int>(m_dimensions.y),
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);
	m_frameCount = SDL_GetPerformanceCounter();
}

Window::~Window()
{
	SDL_DestroyWindow(m_sdlWindow);
	SDL_Quit();
}

SDL_GLContext Window::createContext() const
{
	const auto glContext = SDL_GL_CreateContext(m_sdlWindow);
	SDL_GL_MakeCurrent(m_sdlWindow, glContext);
	return glContext;
}

void Window::run()
{
	init();
	while (!m_shouldClose)
	{
		handleEvents();
		update(calcDeltaTime());
		SDL_GL_SwapWindow(m_sdlWindow);
	}
}

void Window::close()
{
	m_shouldClose = true;
}

void Window::onResize(const glm::uvec2& windowDimensions)
{
	m_dimensions = windowDimensions;
	glViewport(
		0,
		0,
		static_cast<int>(m_dimensions.x),
		static_cast<int>(m_dimensions.y)
	);
}

bool Window::isKeyDown(SDL_Keycode keycode)
{
	return m_keyboardState[keycode];
}

bool Window::isKeyPressed(SDL_Keycode keycode)
{
	return m_keyboardState[keycode] && !m_lastKeyboardState[keycode];
}

bool Window::isKeyReleased(SDL_Keycode keycode)
{
	return !m_keyboardState[keycode] && m_lastKeyboardState[keycode];
}

bool Window::isMouseButtonDown(uint8_t mouseButton)
{
	return m_mouseState[mouseButton];
}

bool Window::isMouseButtonPressed(uint8_t mouseButton)
{
	return m_mouseState[mouseButton] && !m_lastMouseState[mouseButton];
}

bool Window::isMouseButtonReleased(uint8_t mouseButton)
{
	return !m_mouseState[mouseButton] && m_lastMouseState[mouseButton];
}

const glm::vec2& Window::getMousePosition() const
{
	return m_mousePosition;
}

glm::vec2 Window::getMouseDelta() const
{
	return m_mousePositionLastFrame - m_mousePosition;
}

void Window::handleEvents()
{
	m_lastKeyboardState = m_keyboardState;
	m_lastMouseState = m_mouseState;
	m_mousePositionLastFrame = m_mousePosition;
	SDL_Event m_event;
	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			close();
			break;
		case SDL_WINDOWEVENT:
			if (m_event.window.event == SDL_WINDOWEVENT_RESIZED)
				onResize({m_event.window.data1, m_event.window.data2});
			break;
		case SDL_KEYDOWN:
			m_keyboardState[m_event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			m_keyboardState[m_event.key.keysym.sym] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_mouseState[m_event.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			m_mouseState[m_event.button.button] = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition = {m_event.button.x, m_event.button.y};
			break;
		default:
			break;
		}
	}
}

float Window::calcDeltaTime()
{
	const uint64_t lastFrameCount = m_frameCount;
	m_frameCount = SDL_GetPerformanceCounter();
	const double deltaTime = (m_frameCount - lastFrameCount)
		/ static_cast<double>(SDL_GetPerformanceFrequency());
	return static_cast<float>(glm::max(deltaTime, 0.0001));
}

void Window::setTitle(const std::string& title)
{
	m_title = title;
	SDL_SetWindowTitle(m_sdlWindow, m_title.c_str());
}

void Window::setDimensions(const glm::uvec2& dimensions)
{
	m_dimensions = dimensions;
	SDL_SetWindowSize(
		m_sdlWindow,
		static_cast<int>(m_dimensions.x),
		static_cast<int>(m_dimensions.y)
	);
}
