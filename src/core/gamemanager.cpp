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
#include <sparky\core\gamemanager.hpp>			// Class definition.
#include <sparky\core\scene.hpp>				// The scenes to render and update.
#include <sparky\rendering\ambientshader.hpp>	// Global ambience.
#include <sparky\rendering\finalshader.hpp>		// The final shader that renders the scene.
#include <sparky\rendering\meshdata.hpp>		// The mesh that the scene rendering is rendered onto.
#include <sparky\math\frustum.hpp>				// The frustum needs to be constructed before rendering.
#include <sparky\core\window.hpp>				// Window needs to be cleared and swapped.
#include <sparky\input\eventmanager.hpp>		// Events need to be polled and handled.
#include <sparky\core\pool.hpp>					// Releases un-referenced dynamic objects.
#include <sparky\utils\gldevice.hpp>			// Glew initialisation.
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
		: Singleton<GameManager>(), m_scenes(), m_pAmbient(nullptr), m_pShader(nullptr), m_pQuad(nullptr), 
			m_directionalLights(), m_pointLights(), m_pActiveDirectional(nullptr), m_pActivePoint(nullptr), m_buffer()
	{
	}

	////////////////////////////////////////////////////////////
	GameManager::~GameManager(void)
	{
		Ref::release(m_pQuad);
		Ref::release(m_pAmbient);
		Ref::release(m_pShader);

		for (auto& scene : m_scenes)
		{
			Ref::release(scene);
		}
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	DirectionalLight* GameManager::getActiveDirectional(void) const
	{
		return m_pActiveDirectional;
	}

	////////////////////////////////////////////////////////////
	PointLight* GameManager::getActivePoint(void) const
	{
		return m_pActivePoint;
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

		m_pShader = new FinalShader();
		m_pShader->addRef();

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
	void GameManager::addDirectionalLight(DirectionalLight* pLight)
	{
		m_directionalLights.push_back(pLight);
	}

	////////////////////////////////////////////////////////////
	void GameManager::addPointLight(PointLight* pLight)
	{
		m_pointLights.push_back(pLight);
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

			m_pShader->bind();

			for (const auto& light : m_directionalLights)
			{
				m_pActiveDirectional = light;
				m_pShader->update(Transform());

				m_pQuad->render();
			}

			m_pShader->unbind();

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