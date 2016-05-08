#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>

#include <sparky\core\window.hpp>
#include <sparky\utils\gldevice.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\rendering\deferredshader.hpp>
#include <sparky\rendering\ambientshader.hpp>
#include <sparky\rendering\directionalshader.hpp>
#include <sparky\rendering\pointshader.hpp>
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

	GameManager::getInstance().init();

	ResourceManager::getInstance().addShader("deferred",    new DeferredShader());
	ResourceManager::getInstance().addShader("ambient",     new AmbientShader());
	ResourceManager::getInstance().addShader("directional", new DirectionalShader());
	ResourceManager::getInstance().addShader("point",       new PointShader());

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