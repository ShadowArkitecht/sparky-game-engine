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
Ctor and Dtor
====================
*/
#include <sparky\input\mouse.hpp>	// Class definition.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Mouse::Mouse(void)
		: IEventComponent(), m_currentButtons(), m_downButtons(), m_upButtons(), m_position(), m_delta()
	{
		m_currentButtons.fill(false);
		m_downButtons.fill(false);
		m_upButtons.fill(false);
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	const Vector2i& Mouse::getPosition(void) const
	{
		return m_position;
	}

	////////////////////////////////////////////////////////////
	const Vector2i& Mouse::getDelta(void) const
	{
		return m_delta;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	bool Mouse::getButton(const eMouseButton button)
	{
		return m_currentButtons.at(static_cast<int>(button));
	}

	////////////////////////////////////////////////////////////
	bool Mouse::getButtonDown(const eMouseButton button)
	{
		return m_downButtons.at(static_cast<int>(button));
	}

	////////////////////////////////////////////////////////////
	bool Mouse::getButtonUp(const eMouseButton button)
	{
		return m_upButtons.at(static_cast<int>(button));
	}

	////////////////////////////////////////////////////////////
	void Mouse::update(const SDL_Event& e)
	{
		m_delta = Vector2i::zero();
		Uint8 button = e.button.button;

		m_downButtons.fill(false);
		m_upButtons.fill(false);

		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (button == SDL_BUTTON_LEFT)
			{
				m_currentButtons.at(0) = true;
				m_downButtons.at(0)    = true;
			}

			if (button == SDL_BUTTON_RIGHT)
			{
				m_currentButtons.at(1) = true;
				m_downButtons.at(1)    = true;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (button == SDL_BUTTON_LEFT)
			{
				m_upButtons.at(0)	   = true;
				m_currentButtons.at(0) = false;
			}

			if (button == SDL_BUTTON_RIGHT)
			{
				m_upButtons.at(1)      = true;
				m_currentButtons.at(1) = false;
			}
			break;

		case SDL_MOUSEMOTION:
			m_position.x = e.motion.x;
			m_position.y = e.motion.y;

			m_delta.x = e.motion.xrel;
			m_delta.y = e.motion.yrel;

			break;
		}
	}

}//namespace sparky