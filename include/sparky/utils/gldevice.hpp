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

#ifndef __SPARKY_GLDEVICE_HPP__
#define __SPARKY_GLDEVICE_HPP__

/*
====================
Additional Includes
====================
*/
#include <GLEW\glew.h>	// GLDevice needs access to OpenGL functionality.

namespace sparky
{
	class GLDevice final
	{
	public:
		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Initialise GLEW and its extensions for use.
		///
		/// Before any OpenGL functionality can be utilised within the
		/// application, GLEW has to be initialised so that it can 
		/// operate. The initlialisation must be called after the 
		/// context has been created with the sparky::Window.
		///
		////////////////////////////////////////////////////////////
		static void init(void);

		////////////////////////////////////////////////////////////
		/// \brief Changes all of the objects within a scene to only render
		///		   their wireframe.
		////////////////////////////////////////////////////////////
		static void enableWireframe(void);

		////////////////////////////////////////////////////////////
		/// \brief Enables a mode within OpenGL.
		////////////////////////////////////////////////////////////
		static void enable(GLenum mode);

		////////////////////////////////////////////////////////////
		/// \brief Disables a mode within OpenGL.
		////////////////////////////////////////////////////////////
		static void disable(GLenum mode);
	};

}//namespace sparky

#endif//__SPARKY_GLDEVICE_HPP__