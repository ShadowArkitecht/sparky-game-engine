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

#include <sparky\rendering\imesh.hpp>	// Class definition.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	IMeshComponent::IMeshComponent(void)
		: Ref(), m_vertices(), m_indices(), m_buffer(), m_arrayBuffer(), m_generated(false)
	{
	}

	////////////////////////////////////////////////////////////
	IMeshComponent::~IMeshComponent(void)
	{
		this->clear();
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	bool IMeshComponent::isGenerated(void) const
	{
		return m_generated;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void IMeshComponent::addVertex(const Vertex_t& vertex)
	{
		m_vertices.push_back(vertex);
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::addIndex(const GLuint index)
	{
		m_indices.push_back(index);
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::addFace(const Vertex_t& v1, const Vertex_t& v2, const Vertex_t& v3, const Vertex_t& v4, const bool order)
	{
		int index = m_vertices.size();

		this->addVertex(v1);
		this->addVertex(v2);
		this->addVertex(v3);
		this->addVertex(v4);

		if (!order)
		{
			this->addIndex(index);
			this->addIndex(index + 1);
			this->addIndex(index + 2);
			this->addIndex(index + 2);
			this->addIndex(index + 3);
			this->addIndex(index);
		}
		else
		{
			this->addIndex(index);
			this->addIndex(index + 3);
			this->addIndex(index + 2);
			this->addIndex(index + 2);
			this->addIndex(index + 1);
			this->addIndex(index);
		}
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::clear(void)
	{
		m_vertices.clear();
		m_indices.clear();
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::reset(void)
	{
		this->clear();
		m_generated = false;
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::generate(void)
	{
		if (!m_generated)
		{
			if (!m_vertices.empty())
			{
				m_arrayBuffer.generate();
				m_arrayBuffer.bind();

				m_buffer.generate();

				m_buffer.bind(m_vertices, m_indices);

				m_buffer.enableAttributes();

				m_arrayBuffer.unbind();
			}

			m_generated = true;
		}
	}

}//namespace sparky