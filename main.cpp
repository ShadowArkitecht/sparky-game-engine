#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>

#include <sparky\core\window.hpp>
#include <sparky\utils\gldevice.hpp>
#include <sparky\utils\config.hpp>
#include <sparky\rendering\meshdata.hpp>
#include <sparky\rendering\basicshader.hpp>
#include <sparky\math\transform.hpp>
#include <sparky\core\camera.hpp>
#include <sparky\rendering\texture.hpp>
#include <sparky\input\eventmanager.hpp>
#include <sparky\input\input.hpp>
#include <sparky\core\pool.hpp>
#include <sparky\core\resourcemanager.hpp>

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

	Camera camera;
	camera.create(file);

	camera.getTransform().setPosition(Vector3f(0.0f, 0.0f, -5.0f));

	ResourceManager::getInstance().addShader("basic", new BasicShader());
	BasicShader* pShader = ResourceManager::getInstance().getShader<BasicShader>("basic");

	MeshData* pMesh = new MeshData();
	pMesh->addRef();

	Input* pInput = new Input();

	pMesh->addFace(Rectf(-0.5f, -0.5f, 1.0f, 1.0f), false);
	pMesh->generate(true);

	SPARKY_TEXTURE_DESC desc;
	memset(&desc, 0, sizeof(desc));

	desc.target         = GL_TEXTURE_2D;
	desc.internalFormat = GL_RGB;
	desc.filter			= eTextureFilter::NEAREST;
	desc.mode			= eTextureWrapMode::REPEAT;

	Texture* pTexture = new Texture("assets/tilesheet.png", desc);
	pTexture->addRef();

	while (window.isRunning())
	{
		window.clear();

		pShader->bind();
		pTexture->bind();

		pShader->update(Transform());

		pMesh->render();

		pTexture->unbind();
		pShader->unbind();

		window.swap();

		if (pInput->getKey(SDLK_w))
		{
			Camera::getMain().getTransform().translate(Camera::getMain().getTransform().forward() * 15.0f * 0.0016f);
		}
		if (pInput->getKey(SDLK_s))
		{
			Camera::getMain().getTransform().translate(-Camera::getMain().getTransform().forward() * 15.0f * 0.0016f);
		}
		if (pInput->getKey(SDLK_d))
		{
			Camera::getMain().getTransform().translate(Camera::getMain().getTransform().right() * 15.0f * 0.0016f);
		}
		if (pInput->getKey(SDLK_a))
		{
			Camera::getMain().getTransform().translate(-Camera::getMain().getTransform().right() * 15.0f * 0.0016f);
		}
		if (pInput->getKey(SDLK_i))
		{
			Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::right(), -300.0f * 0.0016f));
		}
		if (pInput->getKey(SDLK_k))
		{
			Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::right(), 300.0f * 0.0016f));
		}
		if (pInput->getKey(SDLK_l))
		{
			Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::up(), 300.0f * 0.0016f));
		}
		if (pInput->getKey(SDLK_j))
		{
			Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::up(), -300.0f * 0.0016f));
		}

		EventManager::getInstance().poll();
		PoolManager::getInstance().flush();
	}

	SDL_Quit();

	return 0;
}