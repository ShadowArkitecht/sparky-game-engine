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
#include <GLEW\glew.h>					// For the linking of shaders to the Program ID.

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
		GLuint					 m_ID;		// The ID of the program. This is used to bind and unbind shader behaviour.
		std::vector<GLSLObject*> m_shaders; // The shaders attached to the Program.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit Program(void);
		~Program(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		GLuint getID(void) const;

		/*
		====================
		Methods
		====================
		*/
		void attachShader(GLSLObject* pObject);
		void link(void);
		void bind(void) const;
		void unbind(void) const;
	};

}//namespace hydra

#endif//__HYDRA_PROGRAM_HPP__