#include "game.hpp"
#include <sparky\utils\string.hpp>
#include <sparky\core\camera.hpp>
#include <sparky\core\resourcemanager.hpp>
#include <sparky\utils\gldevice.hpp>
#include <sparky\generation\chunk.hpp>
#include <sparky\utils\threadmanager.hpp>

using namespace sparky;

Game::Game(void)
	: m_pWorld(nullptr), m_pTexture(nullptr), m_pInput(nullptr), m_pLight(nullptr)
{
	m_pWorld = new World();
	m_pWorld->addRef();

	m_pWorld->addChunk(Vector3i(0, 0, 0));

	SPARKY_TEXTURE_DESC desc;
	memset(&desc, 0, sizeof(SPARKY_TEXTURE_DESC));

	desc.target			= GL_TEXTURE_2D;
	desc.internalFormat = GL_RGB;
	desc.filter			= eTextureFilter::NEAREST;
	desc.mode			= eTextureWrapMode::REPEAT;

	m_pTexture = new Texture("assets/tilesheet.png", desc);
	m_pTexture->addRef();

	m_pInput = new Input();

	SPARKY_DIRECTIONAL_LIGHT_DESC dl;
	memset(&dl, 0, sizeof(SPARKY_DIRECTIONAL_LIGHT_DESC));

	dl.base.name = String("u_light");
	dl.base.position = Vector3f::one();
	dl.base.colour = Vector3f(0.5f, 0.0f, 0.0f);
	dl.base.intensity = 10.0f;

	dl.direction = Vector3f(1.0f, 0.0f, 0.0f);

	m_pLight = new DirectionalLight(dl);
	m_pLight->addRef();

	dl.base.colour = Vector3f(0.0f, 0.0f, 1.0f);
	dl.direction = Vector3f(-1.0f, 0.0f, 0.0f);

	m_pLight2 = new DirectionalLight(dl);
	m_pLight2->addRef();

	m_pShader = ResourceManager::getInstance().getShader<DeferredShader>("deferred");
}

Game::~Game(void)
{
	Ref::release(m_pTexture);
	Ref::release(m_pWorld);
}

void Game::update(void)
{
	m_pLight->addLight();
	m_pLight2->addLight();

	if (m_pInput->getKey(SDLK_w))
	{
		Camera::getMain().getTransform().translate(Camera::getMain().getTransform().forward() * 15.0f * 0.0016f);
	}
	if (m_pInput->getKey(SDLK_s))
	{
		Camera::getMain().getTransform().translate(-Camera::getMain().getTransform().forward() * 15.0f * 0.0016f);
	}
	if (m_pInput->getKey(SDLK_d))
	{
		Camera::getMain().getTransform().translate(Camera::getMain().getTransform().right() * 15.0f * 0.0016f);
	}
	if (m_pInput->getKey(SDLK_a))
	{
		Camera::getMain().getTransform().translate(-Camera::getMain().getTransform().right() * 15.0f * 0.0016f);
	}
	if (m_pInput->getKey(SDLK_i))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::right(), -300.0f * 0.0016f));
	}
	if (m_pInput->getKey(SDLK_k))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::right(), 300.0f * 0.0016f));
	}
	if (m_pInput->getKey(SDLK_l))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::up(), 300.0f * 0.0016f));
	}
	if (m_pInput->getKey(SDLK_j))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::up(), -300.0f * 0.0016f));
	}

	//m_pWorld->getChunk(0, 0, 0)->getTransform().rotate(Quaternionf::angleAxis(Vector3f::up(), 20.0f * 0.0016f));
}

void Game::render(void)
{
	m_pShader->bind();
	m_pTexture->bind();

	m_pWorld->render(m_pShader);

	m_pTexture->unbind();
	m_pShader->unbind();
}