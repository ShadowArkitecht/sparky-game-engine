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

#ifndef __SPARKY_GLSL_OBJECT_HPP__
#define __SPARKY_GLSL_OBJECT_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>					// Storage container for includes already loaded in.
/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>	    // GLSLObject will be a dynamically allocated object, therefore it needs to inherit from Object.
#include <sparky\utils\string.hpp>	// Needs the filename and source to be string instances.
/*
====================
Additional Includes
====================
*/
#include <GL\glew.h>				// Shader loading and compilation.

namespace sparky
{
	/*
	====================
	Enumerations
	====================
	*/
	enum class eShaderType
	{
		VERTEX,
		FRAGMENT
	};

	class GLSLObject final : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		GLuint				m_ID;		///< ID of the shader. The shader is compiled and bound into this variable.
		String				m_filename;	///< File location of the source.
		String				m_source;	///< Source ( text ) form of the shader.
		GLuint				m_type;		///< Type of shader, set to GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
		bool		        m_compiled;	///< Whether the shader has been compiled.
		std::vector<String> m_includes;	///< All includes in the file, checks and prevents the same includes.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Parses the shader text file.
		///
		/// When the shader is parsed, it is error checked for the correct 
		/// file location and presents an error if the shader cannot be found. 
		/// The parser will store the shader within a source string, additional 
		/// support for  include statements has been provided, which will be 
		/// recursively parsed and added to the source string.
		/// 
		/// \param filename		The filename.
		///
		/// \retval bool	True if the shader and its include have been parsed.
		///
		////////////////////////////////////////////////////////////
		bool parse(const String& filename);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a Shader object with a filename and type.
		///
		/// Constructs a new Shader object by loading the shader from the
		/// specified filename and setting its type. Construction will fail
		/// if the filename is not a valid shader or does not end in the
		/// extension .glsl.
		///
		/// \param filename		The file directory of the shader.
		/// \param type			The type of shader being parsed.
		///
		////////////////////////////////////////////////////////////
		explicit GLSLObject(const String& filename, const eShaderType type);

		////////////////////////////////////////////////////////////
		/// \brief Destructor for the GLSLObject object.
		///
		/// When the destructor is called, the shader text is cleared
		/// and the Shaders ID is deleted.
		///
		////////////////////////////////////////////////////////////
		~GLSLObject(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the ID of the Shader object.
		///
		/// \retval GLuint	The Shader ID.
		///
		////////////////////////////////////////////////////////////
		GLuint getID(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the compilation state of the Shader object.
		///
		/// \retval bool	True if the Shader has been compiled.
		///
		////////////////////////////////////////////////////////////
		bool isCompiled(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Compiles the Shader object for use.
		/// 
		/// When the Shader is compiled, it checks to see if it has
		/// been compiled already. If it has not, the Shader will 
		/// compile and provide error checking. If there were no errors
		/// the Shader is successfully compiled for use.
		///
		////////////////////////////////////////////////////////////
		void compile(void);
	};

}//namespace sparky

#endif//__SPARKY_GLSL_OBJECT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::GLSLObject
/// \ingroup rendering
///
/// sparky::GLSLObject is a OpenGL Shader wrapper class for
/// easily loading, parsing and compiling GLSL shaders. It provides
/// additional error checking and helper methods for making
/// compilation as simple as possible.
///
/// sparky::GLSLObject is often used in conjunction with 
/// sparky::Program, which provides additional functionality
/// for Shader objects.
///
/// Due to the generic nature of the class, it can be used for 
/// compilation of any shader that the user provides it with.
/// For a code example please refer to sparky::Program.
///
////////////////////////////////////////////////////////////
