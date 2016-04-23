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
#include <GLEW\glew.h>				// Shader loading and compilation.

namespace sparky
{
	/*
	====================
	Enumerations
	====================
	*/
	enum class eShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER
	};

	class GLSLObject final : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		GLuint				m_ID;		// ID of the shader. The shader is compiled and bound into this variable.
		String				m_filename;	// File location of the source.
		String				m_source;	// Source ( text ) form of the shader.
		GLuint				m_type;		// Type of shader, set to GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
		bool		        m_compiled;	// Whether the shader has been compiled.
		std::vector<String> m_includes;	// All includes in the file, checks and prevents the same includes.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		bool parse(const String& filename);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit GLSLObject(const String& filename, const eShaderType type);
		~GLSLObject(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		unsigned int getID(void) const;
		bool isCompiled(void) const;

		/*
		====================
		Methods
		====================
		*/
		void compile(void);
	};

}//namespace sparky

#endif//__SPARKY_GLSL_OBJECT_HPP__