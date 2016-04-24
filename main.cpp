#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>
#include <GLEW\glew.h>

#include <sparky\utils\debug.hpp>
#include <sparky\core\window.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\generation\chunk.hpp>

#include <sparky\rendering\basicshader.hpp>
#include <sparky\utils\threadpool.hpp>
#include <sparky\math\transform.hpp>
#include <sparky\core\resourcemanager.hpp>

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

	ThreadPool pool;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	ResourceManager::getInstance().addShader("basic", new BasicShader());

	BasicShader* pShader = static_cast<BasicShader*>(ResourceManager::getInstance().getShader("basic"));

	Chunk* pChunk = new Chunk();

	pool.addTask(std::bind(&Chunk::greedy, pChunk));

	pChunk->addRef();

	Transform t;
	t.setPosition(Vector3f(0.0f, 0.0f, 0.0f));

	while (window.isRunning())
	{
		t.setRotation(t.getRotation() * Quaternionf::angleAxis(Vector3f::up(), 5.0f * 0.0016f));

		window.clear();

		pShader->bind();
		pShader->update(t);

		pChunk->render();

		pShader->unbind();

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