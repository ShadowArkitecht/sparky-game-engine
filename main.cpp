#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>

#include <sparky\core\window.hpp>
#include <sparky\utils\gldevice.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\rendering\deferredshader.hpp>
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

	Matrix4f test;
	test.setRow(0, Vector4f(5.0, 7.0f, 9.0f, 1.0f));

	std::cout << test << std::endl;
	std::cout << Matrix4f::transpose(test) << std::endl;

	GameManager::getInstance().init();

	ResourceManager::getInstance().addShader("deferred", new DeferredShader());

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