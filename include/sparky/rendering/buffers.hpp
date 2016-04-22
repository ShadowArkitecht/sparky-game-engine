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

#ifndef __SPARKY_BUFFERS_HPP__
#define __SPARKY_BUFFERS_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>						// Passed in to method for reading vertex and index information.
/*
====================
Class Includes
====================
*/
#include <sparky\rendering\vertex.hpp>	// The vertices have to be read to generate and bind meshes.
/*
====================
Additional Includes
====================
*/
#include <GLEW\glew.h>					// OpenGL functionality.

namespace sparky
{
	/*
	====================
	Enumerations
	====================
	*/
	enum eAttributeLocation
	{
		ATTRIB_LOCATION_VERTEX,
		ATTRIB_LOCATION_NORMAL,
		ATTRIB_LOCATION_UV
	};

	class Buffer final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		GLuint m_vbo;	// Vertex Buffer Object.
		GLuint m_ibo;	// Index Buffer Object.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of a Buffer object.
		///
		/// The default constructor of a Buffer object will construct
		/// the Buffer and sets the buffer objects to default values.
		///
		////////////////////////////////////////////////////////////
		explicit Buffer(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of a Buffer object.
		///
		/// When the buffer is destroyed, it deletes the buffer objects
		/// on the GPU and de-allocates the memory for use.
		///
		////////////////////////////////////////////////////////////
		~Buffer(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Generates the buffers.
		///
		/// When a buffer is generated, a segment of memory on the GPU
		/// is dedicated to the information stored within the respective
		/// buffers, when the object are bound or enabled, the information
		/// is retrieved for rendering.
		///
		////////////////////////////////////////////////////////////
		void generate(void);

		////////////////////////////////////////////////////////////
		/// \brief Bind the information for the buffers.
		///
		/// The buffers are populated with the information of a specific
		/// mesh, so that when the buffers are bound and used, it knows
		/// the vertex and index information to display to the frame.
		///
		/// \param vertices		The vertices of the mesh to populate the buffer with.
		/// \param indices		The indices of the mesh to populate the buffer with.
		///
		////////////////////////////////////////////////////////////
		void bind(const std::vector<Vertex_t>& vertices, const std::vector<GLuint>& indices);

		////////////////////////////////////////////////////////////
		/// \brief Enable the attributes of the vertices.
		/// 
		/// When an attribute is enabled, it allows for easy communication
		/// between the vertex information and GLSL shaders.
		///
		////////////////////////////////////////////////////////////
		void enableAttributes(void);

		////////////////////////////////////////////////////////////
		/// \brief Disable the attributes of the vertices.
		/// 
		/// When an attribute is disabled, it breaks the communication
		/// between the vertex information and the GLSL shaders.
		///
		////////////////////////////////////////////////////////////
		void disableAttributes(void);
	};


	class ArrayBuffer final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		GLuint m_vao;	// Vertex Array Object.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Array Buffer object.
		///
		/// The default construction of the Array Buffer object sets the
		/// member variables to default values.
		///
		////////////////////////////////////////////////////////////
		explicit ArrayBuffer(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Array Buffer object.
		///
		/// The destruction of the Array Buffer object deletes the 
		/// information retained by the vertex array object.
		///
		////////////////////////////////////////////////////////////
		~ArrayBuffer(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Generates the vertex array object for use.
		///
		/// A vertex array object stores all of the bound information 
		/// within other buffers and stores it in a array, which when
		/// bound, will bind the other buffers contained within.
		///
		////////////////////////////////////////////////////////////
		void generate(void);

		////////////////////////////////////////////////////////////
		/// \brief Bind the vertex array object.
		////////////////////////////////////////////////////////////
		void bind(void);

		////////////////////////////////////////////////////////////
		/// \brief Unbinds the vertex array object.
		////////////////////////////////////////////////////////////
		void unbind(void);
	};

}//namespace sparky

#endif//__SPARKY_BUFFERS_HPP__