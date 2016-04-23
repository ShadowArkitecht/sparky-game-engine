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
#include <sparky\rendering\program.hpp>	// Class definitions.
#include <sparky\core\ref.hpp>			// For safe releasing.
#include <sparky\utils\debug.hpp>		// For printing out any potential errors to the console buffer.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Program::Program(void)
		: m_ID(0), m_shaders()
	{
	}

	////////////////////////////////////////////////////////////
	Program::~Program(void)
	{
		unbind();

		for (auto& shader : m_shaders)
		{
			Ref::release(shader);
		}

		if (m_ID)
		{
			glDeleteProgram(m_ID);
			m_ID = NULL;
		}
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	GLuint Program::getID(void) const
	{
		return m_ID;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Program::attachShader(GLSLObject* pObject)
	{
		if (pObject)
		{
			pObject->addRef();
			m_shaders.push_back(pObject);
		}
	}

	////////////////////////////////////////////////////////////
	void Program::link(void)
	{
		m_ID = glCreateProgram();

		for (auto& shader : m_shaders)
		{
			if (!shader->isCompiled())
			{
				shader->compile();
			}

			glAttachShader(m_ID, shader->getID());
		}

		glLinkProgram(m_ID);

		GLint linked;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &linked);

		if (linked != GL_TRUE)
		{
			GLint logLength;

			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> errorLog(logLength);
			glGetProgramInfoLog(m_ID, logLength, &logLength, &errorLog[0]);

			DebugLog::warning("Unable to link Program", m_ID, ". ", &errorLog[0]);
			//delete Program if failed 
			glDeleteProgram(m_ID);
			//release shaders
			for (auto& shader : m_shaders)
			{
				Ref::release(shader);
			}
		}

		for (const auto& shader : m_shaders)
		{
			glDetachShader(m_ID, shader->getID());
		}
	}

	////////////////////////////////////////////////////////////
	void Program::bind(void) const
	{
		glUseProgram(m_ID);
	}

	////////////////////////////////////////////////////////////
	void Program::unbind(void) const
	{
		glUseProgram(NULL);
	}

}//namespace sparky