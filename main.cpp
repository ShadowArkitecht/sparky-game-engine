#include <iostream>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <GLEW\glew.h>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialise SDL" << SDL_GetError() << std::endl;
		return -1;
	}

	sparky::Window window;
	window.create("Sparky!", sparky::Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), sparky::Vector2i(640, 480));

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		std::cout << "Failed to initalise GLEW." << glewGetErrorString(error) << std::endl;
		return -1;
	}

	while (window.isRunning())
	{
		window.clear();

		window.swap();

		sparky::PoolManager::getInstance().flush();
	}

	getchar();

	SDL_Quit();

	return 0;
}