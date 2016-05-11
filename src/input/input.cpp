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
#include <sparky\input\input.hpp>	// Class definition.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Input::Input(void)
		: IEventComponent(), m_currentKeys(), m_downKeys(), m_upKeys()
	{
		m_currentKeys.fill(false);
		m_downKeys.fill(false);
		m_upKeys.fill(false);
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	bool Input::getKey(const SDL_Keycode& key) const
	{
		if (key < m_currentKeys.size())
		{
			return m_currentKeys.at(key);
		}

		return 0;
	}

	////////////////////////////////////////////////////////////
	bool Input::getKeyDown(const SDL_Keycode& key) const
	{
		if (key < m_downKeys.size())
		{
			return m_downKeys.at(key);
		}

		return 0;
	}

	////////////////////////////////////////////////////////////
	bool Input::getKeyUp(const SDL_Keycode& key) const
	{
		if (key < m_upKeys.size())
		{
			return m_upKeys.at(key);
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Input::update(const SDL_Event& e)
	{
		m_downKeys.fill(false);
		m_upKeys.fill(false);

		SDL_Keycode key = e.key.keysym.sym;

		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (key < m_currentKeys.size())
			{
				m_currentKeys.at(key) = true;
				m_downKeys.at(key) = true;
			}

			break;

		case SDL_KEYUP:
			if (key < m_currentKeys.size())
			{
				m_upKeys.at(key) = true;
				m_currentKeys.at(key) = false;
			}

			break;
		}
	}

}//namespace sparky