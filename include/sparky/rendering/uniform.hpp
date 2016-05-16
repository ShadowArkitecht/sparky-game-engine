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

#ifndef __SPARKY_UNIFORM_HPP__
#define __SPARKY_UNIFORM_HPP__

/*
====================
CPP Includes
====================
*/
#include <utility>					// Needed for using std::forward in the templated public method.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\string.hpp>	// Used to set the name of the uniform value being read from the shader.	
#include <sparky\math\matrix4.hpp>	// Binding matrices, vector3's and vector4's to uniform values.
#include <sparky\math\vector2.hpp>	// Binding vector2's to uniform values.
/*
====================
Additional Includes
====================
*/
#include <GL\glew.h>				// Binding uniform variables to shaders.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class Program;

	class Uniform final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Program* m_pProgram;	///< The program that the uniforms are added to.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Gets the location of the Uniform within the shader.
		///
		/// \param name		The name of the uniform variable.
		///
		////////////////////////////////////////////////////////////
		GLint getLocation(const String& name) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a single integer value.
		///
		/// \param location The location of the variable within the shader.
		/// \param value	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const int value) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a single unsigned integer value.
		///
		/// \param location The location of the variable within the shader.
		/// \param value	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const unsigned int value) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Vector2i value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Vector2i& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a two integer values.
		///
		/// \param location The location of the variable within the shader.
		/// \param x    	The first value to send to the shader.
		/// \param y		The second value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const int x, const int y) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Vector3i value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Vector3i& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a three integer values.
		///
		/// \param location The location of the variable within the shader.
		/// \param x    	The first value to send to the shader.
		/// \param y		The second value to send to the shader.
		/// \param z		The third value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const int x, const int y, const int z) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Vector4i value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Vector4i& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a four integer values.
		///
		/// \param location The location of the variable within the shader.
		/// \param x    	The first value to send to the shader.
		/// \param y		The second value to send to the shader.
		/// \param z		The third value to send to the shader.
		/// \param w		The fourth value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const int x, const int y, const int z, const int w) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a single float value.
		///
		/// \param location The location of the variable within the shader.
		/// \param value	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const float value) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Vector2f value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Vector2f& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains two float values.
		///
		/// \param location The location of the variable within the shader.
		/// \param x    	The first value to send to the shader.
		/// \param y    	The second value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const float x, const float y) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Vector3f value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Vector3f& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains three float values.
		///
		/// \param location The location of the variable within the shader.
		/// \param x    	The first value to send to the shader.
		/// \param y    	The second value to send to the shader.
		/// \param z    	The third value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const float x, const float y, const float z) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Vector4f value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Vector4f& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains four float values.
		///
		/// \param location The location of the variable within the shader.
		/// \param x    	The first value to send to the shader.
		/// \param y    	The second value to send to the shader.
		/// \param z    	The third value to send to the shader.
		/// \param w    	The fourth value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const float x, const float y, const float z, const float w) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the value of a uniform that contains a Matrix4f value.
		///
		/// \param location The location of the variable within the shader.
		/// \param vector	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		void setParameter(GLint location, const Matrix4f& matrix) const;

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Uniform object constructor.
		///
		/// Uniform needs access to the Program and its shader so it
		/// can successfully send uniforms to the shader for use.
		///
		/// \param pProgram		The program containing the shaders.
		///
		////////////////////////////////////////////////////////////
		explicit Uniform(Program* pProgram);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor for Uniform object.
		////////////////////////////////////////////////////////////
		~Uniform(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Sends a value ( by name ) to the programs shaders.
		///
		/// \param name		The name of the uniform in the shader.
		/// \param value	The value to send to the shader.
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		void setParameter(const String& name, T&& value) const;
	};

	////////////////////////////////////////////////////////////
	template <typename T>
	inline void Uniform::setParameter(const String& name, T&& value) const
	{
		setParameter(getLocation(name), std::forward<T>(value));
	}

}//namespace sparky

#endif//__SPARKY_UNIFORM_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Uniform
/// \ingroup rendering
///
/// sparky::Uniform is convenience class for setting the values
/// of uniform variables within a shader. sparky::Uniform provides
/// overrides for all of the most of common GLSL types. Below
/// is a code example:
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
/// // Sets a matrix within the shader to a identity matrix.
/// sparky::Matrix4f identity = sparky::Matrix4f::identity();
///
/// // Send the matrix to the shaders.
/// sparky::Uniform uniform(&program);
///
/// uniform.setParamater("matrix", identity);
/// \endcode
///
////////////////////////////////////////////////////////////