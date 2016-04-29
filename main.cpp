#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>

#include <sparky\core\window.hpp>
#include <sparky\utils\gldevice.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\rendering\basicshader.hpp>
#include <sparky\core\camera.hpp>
#include <sparky\core\resourcemanager.hpp>
#include <sparky\core\gamemanager.hpp>

#include "game.hpp"

using namespace sparky;

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);

	ConfigFile file;
	file.open("data/config.scfg");

	Window window;
	window.create(file);
	window.setMousePosition(Vector2i::zero());

	GLDevice::init();
	GLDevice::enable(GL_DEPTH_TEST);

	ResourceManager::getInstance().addShader("basic", new BasicShader());


	Camera camera;
	camera.create(file);

	camera.getTransform().setPosition(Vector3f(0.0f, 0.0f, -5.0f));
	GameManager::getInstance().pushScene(new Game());

	while (window.isRunning())
	{
		GameManager::getInstance().run();
	}

	SDL_Quit();

	return 0;
}