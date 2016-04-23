/*
====================
Class Includes
====================
*/
#include <sparky\rendering\uniform.hpp>			// Class definition.
#include <sparky\rendering\program.hpp>			// Accessing the location of a uniform needs access to the Program's ID.
/*
====================
Additional Includes
====================
*/
#include <GLEW\glew.h>							// Setting uniform values.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	Uniform::Uniform(Program* pProgram)
		: m_pProgram(pProgram)
	{
	}

	/*
	====================
	Private Methods
	====================
	*/
	GLint Uniform::getLocation(const String& name) const
	{
		return glGetUniformLocation(m_pProgram->getID(), name.getCString());
	}

	void Uniform::setParameter(GLint location, const int value) const
	{
		glUniform1i(location, value);
	}

	void Uniform::setParameter(GLint location, const unsigned int value) const
	{
		glUniform1i(location, value);
	}

	void Uniform::setParameter(GLint location, const Vector2i& vector) const
	{
		glUniform2i(location, vector.x, vector.y);
	}

	void Uniform::setParameter(GLint location, const int x, const int y) const
	{
		setParameter(location, Vector2i(x, y));
	}

	void Uniform::setParameter(GLint location, const Vector3i& vector) const
	{
		glUniform3i(location, vector.x, vector.y, vector.z);
	}

	void Uniform::setParameter(GLint location, const int x, const int y, const int z) const
	{
		setParameter(location, Vector3i(x, y, z));
	}

	void Uniform::setParameter(GLint location, const Vector4i& vector) const
	{
		glUniform4i(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Uniform::setParameter(GLint location, const int x, const int y, const int z, const int w) const
	{
		setParameter(location, Vector4i(x, y, z, w));
	}

	void Uniform::setParameter(GLint location, const float value) const
	{
		glUniform1f(location, value);
	}

	void Uniform::setParameter(GLint location, const Vector2f& vector) const
	{
		glUniform2f(location, vector.x, vector.y);
	}

	void Uniform::setParameter(GLint location, const float x, const float y) const
	{
		setParameter(location, Vector2f(x, y));
	}

	void Uniform::setParameter(GLint location, const Vector3f& vector) const
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Uniform::setParameter(GLint location, const float x, const float y, const float z) const
	{
		setParameter(location, Vector3f(x, y, z));
	}

	void Uniform::setParameter(GLint location, const Vector4f& vector) const
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Uniform::setParameter(GLint location, const float x, const float y, const float z, const float w) const
	{
		setParameter(location, Vector4f(x, y, z, w));
	}

	void Uniform::setParameter(GLint location, const Matrix4f& matrix) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.m[0][0]);
	}

}//namespace hydra