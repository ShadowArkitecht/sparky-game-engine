#include "game.hpp"
#include <sparky\utils\threadmanager.hpp>
#include <sparky\utils\string.hpp>
#include <sparky\core\camera.hpp>
#include <sparky\core\resourcemanager.hpp>
#include <sparky\utils\gldevice.hpp>

using namespace sparky;

Game::Game(void)
	: m_pChunk(nullptr), m_pTexture(nullptr), m_pInput(nullptr)
{
	m_pChunk = new Chunk();
	m_pChunk->addRef();

	ThreadManager::getInstance().addTask(std::bind(&Chunk::greedy, m_pChunk));

	SPARKY_TEXTURE_DESC desc;
	memset(&desc, 0, sizeof(SPARKY_TEXTURE_DESC));

	desc.target			= GL_TEXTURE_2D;
	desc.internalFormat = GL_RGB;
	desc.filter			= eTextureFilter::NEAREST;
	desc.mode			= eTextureWrapMode::REPEAT;

	m_pTexture = new Texture("assets/tilesheet.png", desc);
	m_pTexture->addRef();

	m_pInput = new Input();

	m_pShader = ResourceManager::getInstance().getShader<BasicShader>("basic");
}

Game::~Game(void)
{
	Ref::release(m_pTexture);
	Ref::release(m_pChunk);
}

void Game::update(void)
{
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

	if (m_pInput->getKey(SDLK_q))
	{
		GLDevice::enableWireframe();
	}
}

void Game::render(void)
{
	m_pShader->bind();
	m_pTexture->bind();

	m_pChunk->render(m_pShader);

	m_pTexture->unbind();
	m_pShader->unbind();
}