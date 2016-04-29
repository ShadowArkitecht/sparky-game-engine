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
#include <sparky\core\gamemanager.hpp>		// Class definition.
#include <sparky\core\scene.hpp>			// The scenes to render and update.
#include <sparky\math\frustum.hpp>			// The frustum needs to be constructed before rendering.
#include <sparky\core\window.hpp>			// Window needs to be cleared and swapped.
#include <sparky\input\eventmanager.hpp>	// Events need to be polled and handled.
#include <sparky\core\pool.hpp>				// Releases un-referenced dynamic objects.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	GameManager::GameManager(void)
		: Singleton<GameManager>(), m_scenes()
	{
	}

	////////////////////////////////////////////////////////////
	GameManager::~GameManager(void)
	{
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

			Scene* pScene = m_scenes.back();

			Window::getMain().clear();

			pScene->render();

			Window::getMain().swap();

			pScene->update();

			EventManager::getInstance().poll();
			PoolManager::getInstance().flush();
		}
	}

}//namespace sparky