///////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Sparky Engine
// 2016 - Benjamin Carter (benjamin.mark.carter@hotmail.com)
// 
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgement
//    in the product documentation would be appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
====================
Class Includes
====================
*/
#include <sparky\core\gamemanager.hpp>			  // Class definition.
#include <sparky\core\scene.hpp>				  // The scenes to render and update.
#include <sparky\rendering\ambientshader.hpp>	  // Global ambience.
#include <sparky\rendering\directionalshader.hpp> // The directional shader that renders the directional lights.
#include <sparky\rendering\pointshader.hpp>		  // The point shader that renders the point lights.
#include <sparky\rendering\meshdata.hpp>		  // The mesh that the scene rendering is rendered onto.
#include <sparky\math\frustum.hpp>				  // The frustum needs to be constructed before rendering.
#include <sparky\core\window.hpp>				  // Window needs to be cleared and swapped.
#include <sparky\input\eventmanager.hpp>		  // Events need to be polled and handled.
#include <sparky\core\pool.hpp>					  // Releases un-referenced dynamic objects.
#include <sparky\utils\gldevice.hpp>			  // Glew initialisation.
#include <sparky\math\transform.hpp>

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	GameManager::GameManager(void)
		: Singleton<GameManager>(), m_scenes(), m_pAmbient(nullptr), m_pDirectional(nullptr), m_pPoint(nullptr), m_pQuad(nullptr),
			m_directionalLights(), m_pointLights(), m_buffer()
	{
	}

	////////////////////////////////////////////////////////////
	GameManager::~GameManager(void)
	{
		Ref::release(m_pQuad);
		Ref::release(m_pAmbient);
		Ref::release(m_pDirectional);
		Ref::release(m_pPoint);

		for (auto& scene : m_scenes)
		{
			Ref::release(scene);
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void GameManager::init(void)
	{
		GLDevice::init();

		m_pAmbient = new AmbientShader();
		m_pAmbient->addRef();

		m_pDirectional = new DirectionalShader();
		m_pDirectional->addRef();

		m_pPoint = new PointShader();
		m_pPoint->addRef();

		m_pQuad = new MeshData();
		m_pQuad->addRef();

		m_pQuad->addFace(Rectf(-1.0f, -1.0f, 2.0f, 2.0f), false);
		m_pQuad->generate();

		m_buffer.generate();

		glCullFace(GL_BACK);

		GLDevice::enable(GL_DEPTH_TEST);
		GLDevice::enable(GL_DEPTH_CLAMP);
	}

	////////////////////////////////////////////////////////////
	void GameManager::addLight(DirectionalLight* pLight)
	{
		m_directionalLights.push_back(pLight);
	}

	////////////////////////////////////////////////////////////
	void GameManager::addLight(PointLight* pLight)
	{
		m_pointLights.push_back(pLight);
	}

	////////////////////////////////////////////////////////////
	void GameManager::pushScene(Scene* pScene)
	{
		pScene->addRef();
		m_scenes.push_back(pScene);
	}

	////////////////////////////////////////////////////////////
	void GameManager::popScene(const bool remove)
	{
		if (remove)
		{
			Ref::release(m_scenes.back());
		}

		m_scenes.pop_back();
	}

	////////////////////////////////////////////////////////////
	void GameManager::run(void)
	{
		if (!m_scenes.empty())
		{
			Frustum::construct();
			glDepthMask(GL_TRUE);

			Scene* pScene = m_scenes.back();

			m_buffer.bind();
			Window::getMain().clear();

			pScene->render();

			m_buffer.unbind();

			pScene->update();

			Window::getMain().clear();

			m_buffer.bindTextures();

			GLDevice::enable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(GL_FALSE);

			m_pAmbient->bind();
			m_pAmbient->update(Transform());

			m_pQuad->render();

			m_pAmbient->unbind();

			m_pDirectional->bind();

			for (const auto& light : m_directionalLights)
			{
				m_pDirectional->setActiveLight(light);
				m_pDirectional->update(Transform());

				m_pQuad->render();
			}

			m_pDirectional->unbind();

			m_pPoint->bind();

			for (const auto& light : m_pointLights)
			{
				m_pPoint->setActiveLight(light);
				m_pPoint->update(Transform());

				m_pQuad->render();
			}

			m_pPoint->unbind();

			m_buffer.unbindTextures();

			glDepthMask(GL_FALSE);
			GLDevice::disable(GL_BLEND);

			Window::getMain().swap();

			EventManager::getInstance().poll();
			PoolManager::getInstance().flush();

			m_directionalLights.clear();
			m_pointLights.clear();
		}
	}

}//namespace sparky