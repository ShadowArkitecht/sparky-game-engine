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
	: m_pWorld(nullptr), m_pWorldTexture(nullptr), m_pInput(nullptr), m_pLight(nullptr)
{
	m_pWorld = new World();
	m_pWorld->addRef();

	SPARKY_TEXTURE_DESC desc;
	memset(&desc, 0, sizeof(SPARKY_TEXTURE_DESC));

	desc.target = GL_TEXTURE_2D;
	desc.internalFormat = GL_RGBA;
	desc.filter = eTextureFilter::NEAREST;
	desc.mode = eTextureWrapMode::REPEAT;

	m_pWorldTexture = new Texture("assets/grass.png", desc);
	m_pWorldTexture->addRef();

	m_pObject = new GameObject(Vector3f(-1.0f, 0.0f, 0.0f));
	m_pObject->addRef();

	m_pObject->addComponent(new MeshRenderer(new Model("assets/model.obj"), new Texture("assets/tex_model.png", desc)));

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


	SPARKY_POINT_LIGHT_DESC pl;
	memset(&pl, 0, sizeof(SPARKY_POINT_LIGHT_DESC));

	pl.base.name = String("u_light");
	pl.base.position = Vector3f(7.5f, 3.0f, 0.0f);
	pl.base.colour = Vector3f(0.0f, 0.0f, 1.0f);
	pl.base.intensity = 50.0f;

	pl.attenuation.constant = 1.0f;
	pl.attenuation.linear = 0.7f;
	pl.attenuation.exponent = 1.8f;

	pl.range = 50.0f;

	m_pBluePoint = new PointLight(pl);
	m_pBluePoint->addRef();


	pl.base.position = Vector3f(7.5f, 6.0f, 0.0f);
	pl.base.colour   = Vector3f(1.0f, 0.0f, 0.0f);

	m_pRedPoint = new PointLight(pl);
	m_pRedPoint->addRef();

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
	Ref::release(m_pBluePoint);
	Ref::release(m_pRedPoint);

	Ref::release(m_pLight);
	Ref::release(m_pWorldTexture);
	Ref::release(m_pWorld);
}

void Game::update(void)
{
	m_pLight->addLight();
	m_pBluePoint->addLight();
	m_pRedPoint->addLight();

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
	m_pWorldTexture->bind();

	m_pWorld->render(m_pShader);

	m_pWorldTexture->unbind();

	m_pObject->render(m_pShader);

	m_pShader->unbind();
}