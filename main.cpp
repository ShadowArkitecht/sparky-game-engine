#include <iostream>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\utils\config.hpp>
#include <GLEW\glew.h>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialise SDL" << SDL_GetError() << std::endl;
		return -1;
	}

	sparky::ConfigFile file;
	file.open("data/config.scfg");

	sparky::Window window;
	window.create(file);

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