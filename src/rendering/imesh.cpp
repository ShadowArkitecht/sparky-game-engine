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
#include <sparky\rendering\imesh.hpp>	// Class definition.
#include <sparky\utils\debug.hpp>		// Used if the indices are incorrect for vertex normal generation.

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
		this->reset();
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

	////////////////////////////////////////////////////////////
	GLuint IMeshComponent::getVertexCount(void) const
	{
		return m_vertices.size();
	}

	////////////////////////////////////////////////////////////
	GLuint IMeshComponent::getIndexCount(void) const
	{
		return m_indices.size();
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
		GLuint index = m_vertices.size();

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
	void IMeshComponent::addFace(const Rectf& face, const bool order)
	{
		Vertex_t v1(Vector3f(face.position.x,				face.position.y,			   0.0f), Vector2f(0.0f, 0.0f));
		Vertex_t v2(Vector3f(face.position.x + face.size.x, face.position.y,			   0.0f), Vector2f(1.0f, 0.0f));
		Vertex_t v3(Vector3f(face.position.x + face.size.x, face.position.y + face.size.y, 0.0f), Vector2f(1.0f, 1.0f));
		Vertex_t v4(Vector3f(face.position.x,				face.position.y + face.size.y, 0.0f), Vector2f(0.0f, 1.0f));

		this->addFace(v1, v2, v3, v4, order);
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::calculateNormals(void)
	{
		if (m_indices.size() % 3 != 0)
		{
			DebugLog::warning("The indices of the Mesh are not divisable by 3. Normals not generated.");
			return;
		}

		for (GLuint i = 0; i < m_indices.size(); i += 3)
		{
			// create a reference to the three vertices so the information can be altered
			Vertex_t& v0 = m_vertices[m_indices[i + 0]];
			Vertex_t& v1 = m_vertices[m_indices[i + 1]];
			Vertex_t& v2 = m_vertices[m_indices[i + 2]];
			// work out the delta of the three vertices
			Vector3f vect1 = Vector3f(v0.position.x - v1.position.x, v0.position.y - v1.position.y, v0.position.z - v1.position.z);
			Vector3f vect2 = Vector3f(v1.position.x - v2.position.x, v1.position.y - v2.position.y, v1.position.z - v2.position.z);
			// generate the vector perpendicular to the two vectors, and normalise it
			Vector3f cross = Vector3f::cross(vect2, vect1);
			// add this value to the current normal value of the vertices
			v0.normal += cross;
			v1.normal += cross;
			v2.normal += cross;
		}

		for (auto& vertex : m_vertices)
		{
			vertex.normal = vertex.normal.normalised();
		}
	}

	////////////////////////////////////////////////////////////
	void IMeshComponent::calculateFaceNormals(const GLuint start, const bool invert)
	{
		for (GLuint i = start; i < start + 6; i += 3)
		{
			// create a reference to the three vertices so the information can be altered
			Vertex_t& v0 = m_vertices.at(m_indices.at(i + 0));
			Vertex_t& v1 = m_vertices.at(m_indices.at(i + 1));
			Vertex_t& v2 = m_vertices.at(m_indices.at(i + 2));
			// work out the delta of the three vertices
			Vector3f vect1 = Vector3f(v0.position.x - v1.position.x, v0.position.y - v1.position.y, v0.position.z - v1.position.z);
			Vector3f vect2 = Vector3f(v1.position.x - v2.position.x, v1.position.y - v2.position.y, v1.position.z - v2.position.z);
			// generate the vector perpendicular to the two vectors, and normalise it
			Vector3f cross;

			if (invert)
			{
				cross = Vector3f::cross(vect1, vect2);
			}
			else
			{
				cross = Vector3f::cross(vect2, vect1);
			}

			// add this value to the current normal value of the vertices
			v0.normal += cross;
			v1.normal += cross;
			v2.normal += cross;

			v0.normal = v0.normal.normalised();
			v1.normal = v1.normal.normalised();
			v2.normal = v2.normal.normalised();
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
	void IMeshComponent::generate(const bool genNormals/*= false*/)
	{
		if (!m_generated)
		{
			if (!m_vertices.empty())
			{
				if (genNormals)
				{
					this->calculateNormals();
				}

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