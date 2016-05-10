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
#include <sparky\core\time.hpp>	// Class definition.
/*
====================
Additional Includes
====================
*/
#include <SDL2\SDL.h>			// Calculating the ticks of the frame.

namespace sparky
{
	/*
	====================
	Const Variables
	====================
	*/
	////////////////////////////////////////////////////////////
	const float MILLI_SECONDS = 1000.0f;

	/*
	====================
	Static Fields
	====================
	*/
	////////////////////////////////////////////////////////////
	long Time::m_sCurrentTime = 0;
	double Time::m_sDeltaTime = 0.0;
	long Time::m_sLastTime = 0;

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	float Time::getDeltaTime(void)
	{
		return static_cast<float>(m_sDeltaTime / MILLI_SECONDS);
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Time::start(void)
	{
		m_sCurrentTime = SDL_GetTicks();
	}

	////////////////////////////////////////////////////////////
	void Time::stop(void)
	{
		m_sDeltaTime = m_sCurrentTime - m_sLastTime;
		m_sLastTime = m_sCurrentTime;
	}

}//namespace sparky