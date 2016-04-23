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
	Program::Program(void)
		: m_ID(0), m_shaders()
	{
	}

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
	GLuint Program::getID(void) const
	{
		return m_ID;
	}

	/*
	====================
	Methods
	====================
	*/
	void Program::attachShader(GLSLObject* pObject)
	{
		pObject->addRef();
		m_shaders.push_back(pObject);
	}

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

	void Program::bind(void) const
	{
		glUseProgram(m_ID);
	}

	void Program::unbind(void) const
	{
		glUseProgram(0);
	}

}//namespace sparky