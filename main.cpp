#include <sparky\utils\debug.hpp>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\utils\config.hpp>
#include <GLEW\glew.h>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		sparky::DebugLog::error("SDL has failed to initialize.", SDL_GetError());
	}

	sparky::ConfigFile file;
	file.open("data/config.scfg");

	sparky::Window window;
	window.create(file);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	
	if (error != GLEW_OK)
	{
		sparky::DebugLog::error("Failed to initalise GLEW.", glewGetErrorString(error));
	}

	while (window.isRunning())
	{
		window.clear();

		window.swap();

		sparky::PoolManager::getInstance().flush();
	}

	SDL_Quit();

	return 0;
}