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

#include <sparky\rendering\buffers.hpp>		// Class definitions.

namespace sparky
{
	/*
	====================
	Constant Variables
	====================
	*/
	////////////////////////////////////////////////////////////
	const int VERTEX_ELEMENTS = 3;
	const int TEXTURE_ELEMENTS = 2;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// BUFFER
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Buffer::Buffer(void)
		: m_vbo(0), m_ibo(0)
	{
	}

	////////////////////////////////////////////////////////////
	Buffer::~Buffer(void)
	{
		this->disableAttributes();

		if (m_ibo)
		{
			glDeleteBuffers(1, &m_ibo);
			m_ibo = NULL;
		}

		if (m_vbo)
		{
			glDeleteBuffers(1, &m_vbo);
			m_vbo = NULL;
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Buffer::generate(void)
	{
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
	}

	////////////////////////////////////////////////////////////
	void Buffer::bind(const std::vector<Vertex_t>& vertices, const std::vector<GLuint>& indices)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_t) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

		GLsizei stride = (VERTEX_ELEMENTS + VERTEX_ELEMENTS + TEXTURE_ELEMENTS) * sizeof(GLfloat);

		glVertexAttribPointer(ATTRIB_LOCATION_VERTEX, VERTEX_ELEMENTS,  GL_FLOAT, GL_FALSE, stride, (void*)0);
		glVertexAttribPointer(ATTRIB_LOCATION_NORMAL, VERTEX_ELEMENTS,  GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(ATTRIB_LOCATION_UV,     TEXTURE_ELEMENTS, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(GLfloat)));
	}

	////////////////////////////////////////////////////////////
	void Buffer::enableAttributes(void)
	{
		glEnableVertexAttribArray(ATTRIB_LOCATION_VERTEX);
		glEnableVertexAttribArray(ATTRIB_LOCATION_NORMAL);
		glEnableVertexAttribArray(ATTRIB_LOCATION_UV);
	}

	////////////////////////////////////////////////////////////
	void Buffer::disableAttributes(void)
	{
		glDisableVertexAttribArray(ATTRIB_LOCATION_UV);
		glEnableVertexAttribArray(ATTRIB_LOCATION_NORMAL);
		glDisableVertexAttribArray(ATTRIB_LOCATION_VERTEX);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ARRAY BUFFER
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	ArrayBuffer::ArrayBuffer(void)
		: m_vao(0)
	{
	}

	////////////////////////////////////////////////////////////
	ArrayBuffer::~ArrayBuffer(void)
	{
		if (m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
			m_vao = NULL;
		}
	}

	////////////////////////////////////////////////////////////
	void ArrayBuffer::generate(void)
	{
		glGenVertexArrays(1, &m_vao);
	}

	////////////////////////////////////////////////////////////
	void ArrayBuffer::bind(void)
	{
		glBindVertexArray(m_vao);
	}

	////////////////////////////////////////////////////////////
	void ArrayBuffer::unbind(void)
	{
		glBindVertexArray(NULL);
	}

}//namespace sparky