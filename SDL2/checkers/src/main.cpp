// chnage log
// 2022-06-01 KO.HWADA
// constexpr glm::uvec2 windowDimensions{1280u, 720u};'

#include "Window.h"
#include "GameWindow.h"

int main(int argc, char* argv[])
{
	// constexpr glm::uvec2 windowDimensions{1280u, 720u};
	const glm::uvec2 windowDimensions{1280u, 720u};

	Window* const window = new GameWindow("SDL-Checkers", windowDimensions);

	window->run();

	delete window;
	return 0;
}
