#ifndef __SPARKY_UNIFORM_HPP__
#define __SPARKY_UNIFORM_HPP__

/*
====================
CPP Includes
====================
*/
#include <utility>					// Needed for using std::forward in the templated public method.
//class includes
#include <sparky\utils\string.hpp>	// Used to set the name of the uniform value being read from the shader.	
#include <sparky\math\matrix4.hpp>	// Binding matrices, vector3's and vector4's to uniform values.
#include <sparky\math\vector2.hpp>	// Binding vector2's to uniform values.

#include <GLEW\glew.h>

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
		Program* m_pProgram;	// The program that the uniforms are added to.

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
		void setParameter(GLint location, const int x, const int y, const int z) const;
		void setParameter(GLint location, const Vector4i& vector) const;
		void setParameter(GLint location, const int x, const int y, const int z, const int w) const;
		void setParameter(GLint location, const float value) const;
		void setParameter(GLint location, const Vector2f& vector) const;
		void setParameter(GLint location, const float x, const float y) const;
		void setParameter(GLint location, const Vector3f& vector) const;
		void setParameter(GLint location, const float x, const float y, const float z) const;
		void setParameter(GLint location, const Vector4f& vector) const;
		void setParameter(GLint location, const float x, const float y, const float z, const float w) const;
		void setParameter(GLint location, const Matrix4f& matrix) const;

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit Uniform(Program* pProgram);
		~Uniform(void) = default;

		/*
		====================
		Methods
		====================
		*/
		template <typename T>
		void setParameter(const String& name, T&& value) const;
	};

	template <typename T>
	inline void Uniform::setParameter(const String& name, T&& value) const
	{
		setParameter(getLocation(name), std::forward<T>(value));
	}

}//namespace sparky

#endif//__SPARKY_UNIFORM_HPP__