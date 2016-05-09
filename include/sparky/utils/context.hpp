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

#ifndef __HYDRA_CONTEXT_HPP__
#define __HYDRA_CONTEXT_HPP__

namespace sparky
{
	struct ContextSettings
	{
		/*
		====================
		Member Variables
		====================
		*/
		unsigned int majorVersion;	///< The major version of OpenGL.
		unsigned int minorVersion;	///< The minor version of OpenGl. eg. 3.3.

		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for ContextSettings object.
		///
		/// The ContextSettings object controls the settings of a
		/// a created window instance. It's use is for declaring
		/// when OpenGL functionality the application will utilise.
		///
		////////////////////////////////////////////////////////////
		explicit ContextSettings(void)
			: majorVersion(3), minorVersion(3)
		{
		}

		////////////////////////////////////////////////////////////
		/// \brief Default constructor for ContextSettings object.
		///
		/// The ContextSettings object controls the settings of a
		/// a created window instance. It's use is for declaring
		/// when OpenGL functionality the application will utilise.
		///
		/// \param majorVersion	The major version of OpenGL the application will use.
		/// \param minorVersion The minor version of OpenGL the application will use.
		///
		////////////////////////////////////////////////////////////
		explicit ContextSettings(unsigned int majorVersion, const unsigned int minorVersion)
			: majorVersion(majorVersion), minorVersion(minorVersion)
		{
		}
	};

}//namespace sparky

#endif//__HYDRA_CONTEXT_HPP__

////////////////////////////////////////////////////////////
/// \struct sparky::ContextSettings
/// \ingroup utils
///
/// sparky::ContextSettings is used in conjunction with the 
/// sparky::Window class for initialising the functionality of
/// OpenGL to specific specifications. 
///
/// Usage example:
/// \code 
/// // Create a context and change values
/// ContextSettings context;
/// context.majorVersion = 4;
/// context.minorVersion = 0;
///
/// // Create a new Window.
/// sparky::Window window;
/// window.create("Sparky!", Vector2i(), Vector2i(640, 480), context);
///
/// // Basic Main window loop.
/// while (window.isRunning())
/// {
///		window.clear()
///		// Rendering of objects should go here.
///		window.swap();
/// }
/// \endcode
///
////////////////////////////////////////////////////////////