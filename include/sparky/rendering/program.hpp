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

#ifndef __SPARKY_PROGRAM_HPP__
#define __SPARKY_PROGRAM_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>							// Container method for all the shaders attached to the program.
/*
====================
Class Includes
====================
*/
#include <sparky\rendering\GLSLobject.hpp>	// GLSLObjects are linked within the Program object.
/*
====================
Additional Includes
====================
*/
#include <GLEW\glew.h>						// For the linking of shaders to the Program ID.

namespace sparky
{
	class Program final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		GLuint					 m_ID;		///< The ID of the program. This is used to bind and unbind shader behaviour.
		std::vector<GLSLObject*> m_shaders; ///< The shaders attached to the Program.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Program object.
		////////////////////////////////////////////////////////////
		explicit Program(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Program object.
		///
		/// When the destructor is called, all of the Program's shaders
		/// are released and de-allocated and the ID of the Program
		/// is deleted.
		///
		////////////////////////////////////////////////////////////
		~Program(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the ID of the Program object.
		///
		/// \retval GLuint	The Program ID.
		///
		////////////////////////////////////////////////////////////
		GLuint getID(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Attach a Shader object to the Program.
		///
		/// When an GLSLObject is added to the Program, it is retained
		/// and stored. When the Program is linked, the shaders are 
		/// compiled and linked to Program object.
		///
		/// \param pObject		The Shader object to attach.
		///
		////////////////////////////////////////////////////////////
		void attachShader(GLSLObject* pObject);

		////////////////////////////////////////////////////////////
		/// \brief Link the Program object.
		///
		/// When the Program is linked, all of the attached shaders
		/// are compiled and linked to the Program ID. When the Program
		/// is bound, all of the functionality linked to it will be
		/// executed.
		///
		////////////////////////////////////////////////////////////
		void link(void);

		////////////////////////////////////////////////////////////
		/// \brief Bind the Program ID.
		///
		/// When the Program is bound, the next objects to render
		/// will utilise the Programs shader behaviours.
		///
		////////////////////////////////////////////////////////////
		void bind(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Unbind the Program ID.
		///
		/// When the Program is unbound, the objects will no longer
		/// utilise Programs shader behaviour.
		///
		////////////////////////////////////////////////////////////
		void unbind(void) const;
	};

}//namespace sparky

#endif//__HYDRA_PROGRAM_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Program
/// \ingroup rendering
///
/// The Program class is responsible for the linking and joint compilation 
/// of all attached shaders. The Program class can also bind and unbind 
/// this shader functionality to the currently rendering objects.
///
/// It provides an easy-to-use interface for shader functionality,
/// without the user having to change various states of the engine.
/// Below is a code example of using the Program.
///
/// Usage example:
/// \code
/// // Make a program and add shaders.
/// sparky::Program program;
///
/// program.attachShader(new sparky::GLSLObject("shaders/basic_vertex.glsl",   sparky::eShaderType::VERTEX_SHADER));
/// program.attachShader(new sparky::GLSLObject("shaders/basic_fragment.glsl", sparky::eShaderType::FRAGMENT_SHADER));
///
/// // Link and compile the shaders.
/// program.link();
///
/// // Bind the shader for use.
/// program.bind();
/// \endcode
///
////////////////////////////////////////////////////////////