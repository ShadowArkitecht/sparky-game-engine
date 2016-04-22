#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include <GLEW\glew.h>

#include <sparky\utils\debug.hpp>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\generation\chunk.hpp>

using namespace sparky;

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		DebugLog::error("SDL has failed to initialize.", SDL_GetError());
	}

	ConfigFile file;
	file.open("data/config.scfg");

	Window window;
	window.create(file);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	
	if (error != GLEW_OK)
	{
		DebugLog::error("Failed to initalise GLEW.", glewGetErrorString(error));
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Chunk* pChunk = new Chunk();
	pChunk->greedy();

	pChunk->addRef();

	while (window.isRunning())
	{
		window.clear();

		pChunk->render();

		window.swap();

		sparky::Event e;
		while (window.onEvent(e))
		{
			if (e.type == SDL_QUIT)
			{
				window.setRunning(false);
			}
		}

		sparky::PoolManager::getInstance().flush();
	}

	SDL_Quit();

	return 0;
}