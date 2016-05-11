#include "game.hpp"
#include <sparky\utils\string.hpp>
#include <sparky\core\camera.hpp>
#include <sparky\core\resourcemanager.hpp>
#include <sparky\utils\gldevice.hpp>
#include <sparky\generation\chunk.hpp>
#include <sparky\utils\threadmanager.hpp>
#include <sparky\core\time.hpp>
#include <sparky\rendering\meshrenderer.hpp>
#include <sparky\rendering\model.hpp>
#include <sparky\core\window.hpp>

#include <noise\noise.h>
#include <sparky\ext\noiseutils.h>

using namespace sparky;

Game::Game(void)
	: m_pWorld(nullptr), m_pTexture(nullptr), m_pInput(nullptr), m_pLight(nullptr)
{
	m_pWorld = new World();
	m_pWorld->addRef();

	SPARKY_TEXTURE_DESC desc;
	memset(&desc, 0, sizeof(SPARKY_TEXTURE_DESC));

	desc.target			= GL_TEXTURE_2D;
	desc.internalFormat = GL_RGB;
	desc.filter			= eTextureFilter::NEAREST;
	desc.mode			= eTextureWrapMode::REPEAT;

	m_pTexture = new Texture("assets/tilesheet.png", desc);
	m_pTexture->addRef();

	m_pObject = new GameObject();
	m_pObject->addRef();

	m_pObject->addComponent(new MeshRenderer(new Model("assets/chr_knight.obj"), new Texture("assets/chr_knight.png", desc)));

	m_pInput = new Input();

	SPARKY_DIRECTIONAL_LIGHT_DESC dl;
	memset(&dl, 0, sizeof(SPARKY_DIRECTIONAL_LIGHT_DESC));

	dl.base.name = String("u_light");
	dl.base.position = Vector3f::one();
	dl.base.colour = Vector3f(1.0f, 1.0f, 1.0f);
	dl.base.intensity = 0.8f;

	dl.direction = Vector3f(1.0f, 0.0f, 0.0f);

	m_pLight = new DirectionalLight(dl);
	m_pLight->addRef();

	dl.base.colour = Vector3f(0.0f, 0.0f, 1.0f);
	dl.direction = Vector3f(-1.0f, 0.0f, 0.0f);

	m_pShader = ResourceManager::getInstance().getShader<DeferredShader>("deferred");

	module::Perlin module;
	utils::NoiseMap heightMap;

	utils::NoiseMapBuilderPlane builder;
	builder.SetSourceModule(module);
	builder.SetDestNoiseMap(heightMap);

	builder.SetDestSize(1024, 1024);
	builder.SetBounds(2.0, 6.0, 1.0, 5.0);

	builder.Build();

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				m_pWorld->addChunk(Vector3i(x * 16, y * 16, z * 16));
			}
		}
	}

	//for (int x = 0; x < 256; x++)
	//{
	//	for (int y = 0; y < 256; y++)
	//	{
	//		for (int z = 0; z < 256; z++)
	//		{
	//			m_pWorld->getVoxel(x, y, z)->setActive(false);
	//		}
	//	}
	//}

	for (int x = 0; x < 256; x++)
	{
		for (int z = 0; z < 256; z++)
		{
			float height = (heightMap.GetValue(x, z) * (200.0f) * 1.0f) * 1.0f;
			int h = static_cast<int>(height);

			for (int y = 0; y < h; y++)
			{
				m_pWorld->getVoxel(x, y, z)->setActive(true);
			}
		}
	}

	m_pWorld->build(eMeshingType::GREEDY);
}

Game::~Game(void)
{
	Ref::release(m_pLight);
	Ref::release(m_pTexture);
	Ref::release(m_pWorld);
}

void Game::update(void)
{
	m_pLight->addLight();


	if (m_pInput->getKey(SDLK_w))
	{
		Camera::getMain().getTransform().translate(Camera::getMain().getTransform().forward() * 50.0f * Time::getDeltaTime());
	}

	if (m_pInput->getKey(SDLK_s))
	{
		Camera::getMain().getTransform().translate(-Camera::getMain().getTransform().forward() * 50.0f  * Time::getDeltaTime());
	}

	if (m_pInput->getKey(SDLK_d))
	{
		Camera::getMain().getTransform().translate(Camera::getMain().getTransform().right() * 50.0f  * Time::getDeltaTime());
	}

	if (m_pInput->getKey(SDLK_a))
	{
		Camera::getMain().getTransform().translate(-Camera::getMain().getTransform().right() * 50.0f  * Time::getDeltaTime());
	}


	if (m_pInput->getKey(SDLK_i))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::right(), -50.0f * Time::getDeltaTime()));
	}

	if (m_pInput->getKey(SDLK_k))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::right(), 50.0f * Time::getDeltaTime()));
	}

	if (m_pInput->getKey(SDLK_j))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(-Vector3f::up(), 50.0f * Time::getDeltaTime()));
	}

	if (m_pInput->getKey(SDLK_l))
	{
		Camera::getMain().getTransform().rotate(Quaternionf::angleAxis(Vector3f::up(), 50.0f * Time::getDeltaTime()));
	}

	if (m_pInput->getKey(SDLK_ESCAPE))
	{
		Window::getMain().close();
	}
}

void Game::render(void)
{
	m_pShader->bind();
	m_pTexture->bind();

	m_pWorld->render(m_pShader);

	m_pTexture->unbind();

	m_pObject->render(m_pShader);

	m_pShader->unbind();
}