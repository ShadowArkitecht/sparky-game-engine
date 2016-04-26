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
#include <sparky\core\resourcemanager.hpp>
#include <sparky\utils\defines.hpp>
#include <sparky\rendering\texture.hpp>
#include <sparky\generation\world.hpp>

#include <SDL_image\SDL_image.h>

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

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	ThreadPool pool;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	ResourceManager::getInstance().addShader("basic", new BasicShader());

	BasicShader* pShader = static_cast<BasicShader*>(ResourceManager::getInstance().getShader("basic"));

	SPARKY_TEXTURE_DESC desc;
	desc.internalFormat = GL_RGB;
	desc.mode = eTextureWrapMode::REPEAT;

	Texture* pTexture = new Texture("assets/tilesheet.png", desc);
	pTexture->addRef();

	World* pWorld = new World();
	pWorld->addRef();

	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			pWorld->addChunk(Vector3i(x * 16, 0, z * 16));
		}
	}

	while (window.isRunning())
	{
		window.clear();

		pShader->bind();
		pTexture->bind();

		pWorld->render(pShader);

		pTexture->unbind();
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