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
CPP Includes
====================
*/
#include <fstream>							// Needed for initially opening and reading the text of the shader file.
/*
====================
Class Includes
====================
*/
#include <sparky\rendering\GLSLobject.hpp>	// Class definition.
#include <sparky\utils\debug.hpp>			// Needed for stating errors that occur during parsing and compilation of shader.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	GLSLObject::GLSLObject(const String& filename, const eShaderType type)
		: Ref(), m_ID(0), m_filename(filename), m_source(), m_type(), m_compiled(false), m_includes()
	{
		if (!m_filename.endsWith(".glsl"))
		{
			DebugLog::error("Shader:", m_filename, "has incorrect file extension.");
		}

		if (!parse(m_filename))
		{
			DebugLog::error("Shader:", m_filename, "has failed to parse.");
		}

		switch (type)
		{
		case eShaderType::VERTEX:
			m_type = GL_VERTEX_SHADER;
			break;

		case eShaderType::FRAGMENT:
			m_type = GL_FRAGMENT_SHADER;
			break;
		}
	}

	////////////////////////////////////////////////////////////
	GLSLObject::~GLSLObject(void)
	{
		m_includes.clear();

		if (m_ID)
		{
			glDeleteShader(m_ID);
			m_ID = NULL;
		}
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	GLuint GLSLObject::getID(void) const
	{
		return m_ID;
	}

	////////////////////////////////////////////////////////////
	bool GLSLObject::isCompiled(void) const
	{
		return m_compiled;
	}

	/*
	====================
	Private Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	bool GLSLObject::parse(const String& filename)
	{
		const String include = "#include";
		std::ifstream file;

		file.open(filename.getCString(), std::ios::in | std::ios::binary);

		if (file.fail())
		{
			DebugLog::warning("Failed to load Shader:", filename);
			return false;
		}

		String line;

		while (file.good())
		{
			//gets the current line from the shader file
			String::getline(file, line);
			//store a temporary line of the current line in the file
			String temp = line;
			//trim it and cut out all whitespace
			temp.trim();
			//checks if the current line is an include
			if (temp.beginsWith(include))
			{
				//get the theoretical location of the opening and closing brackets of the include
				char start = temp[include.getLength()];
				char end = temp[temp.getLength() - 1];
				//checks that the include statement is correctly formatted
				if (start != '"' || end != '"')
				{
					DebugLog::warning("Incorrect include statement in", filename);
					return false;
				}
				//as it is an include statement, we should clear the line before we append, otherwise it will give an
				//error as #include is not a directive of GLSL and will cause compilation errors
				line.clear();
				//get the file name of the include statement
				String includeFile = temp.substring(include.getLength() + 1, temp.getLength() - 1);
				//make sure it has the correct file extension
				if (!includeFile.endsWith(".glsl"))
				{
					DebugLog::error(includeFile, "has incorrect file extension");
				}

				for (const auto& inc : m_includes)
				{
					if (includeFile == inc)
					{
						DebugLog::warning(includeFile, "has already been included in the current context, clearing include.");
						includeFile.clear();
					}
				}

				if (!includeFile.isEmpty())
				{
					m_includes.push_back(includeFile);
					//get the location of the shaders + the file location of the include statement and recursively parse it
					parse(String("shaders/") + includeFile);
				}
			}
			//append the line of the shader to the source
			m_source.append(line);
		}

		return true;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void GLSLObject::compile(void)
	{
		if (!m_compiled)
		{
			//create a LE_Shader id with the type passed in
			GLuint ID = glCreateShader(m_type);
			//convert the file into a char array
			const GLchar* file = m_source.getCString();
			//set the LE_Shader source
			glShaderSource(ID, 1, (const GLchar**)&file, nullptr);
			//compile the LE_Shader
			glCompileShader(ID);
			//error checking
			GLint status;
			glGetShaderiv(ID, GL_COMPILE_STATUS, &status);

			if (status != GL_TRUE)
			{
				DebugLog::warning("Unable to compile shader:", m_filename);

				GLint logSize = 0;
				glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &logSize);

				std::vector<GLchar> errorLog(logSize);
				glGetShaderInfoLog(ID, logSize, &logSize, &errorLog[0]);

				DebugLog::warning(&errorLog[0]);

				glDeleteShader(ID);
				ID = NULL;
			}
			else
			{
				m_ID = ID;
				m_compiled = true;
			}

			m_source.clear();
		}
		else
		{
			DebugLog::warning(m_filename, "has already been compiled.");
		}
	}

}//namespace sparky