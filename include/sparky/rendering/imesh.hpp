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

#ifndef __SPARKY_IMESH_COMPONENT_HPP__
#define __SPARKY_IMESH_COMPONENT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>				// IMeshComponent will be a dynamically allocated object.
#include <sparky\rendering\buffers.hpp>		// OpenGL abstracted buffers.
#include <sparky\math\rect.hpp>				// Rectangles can be used to make 2D faces.

namespace sparky
{
	class IMeshComponent : public Ref
	{
	protected:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<Vertex_t> m_vertices;		///< Vertices of the mesh.
		std::vector<GLuint>	  m_indices;		///< Indices of the mesh.
		Buffer				  m_buffer;			///< The vertex and index buffer.
		ArrayBuffer			  m_arrayBuffer;	///< Array Buffer.

		bool				  m_generated;		///< Whether the Mesh has been generated.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the IMeshComponent object.
		///
		/// The default construction of the IMeshComponent object sets
		/// all of the member variables to default values and inherits
		/// Ref object behaviour.
		///
		////////////////////////////////////////////////////////////
		explicit IMeshComponent(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the IMeshComponent object.
		///
		/// The destruction of the IMeshComponent will clear the vertices
		/// and indices stored by the Mesh.
		///
		////////////////////////////////////////////////////////////
		virtual ~IMeshComponent(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the generated state of the Mesh.
		///
		/// If the objects generate method has not yet been called,
		/// the generated state of the Mesh will be set to false.
		///
		/// \retval bool	True if the object has been generated.
		///
		////////////////////////////////////////////////////////////
		bool isGenerated(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the amount of vertices attached to this Mesh.
		///
		/// \retval GLuint	The amount of vertices.
		///
		////////////////////////////////////////////////////////////
		GLuint getVertexCount(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the amount of indices attached to this Mesh.
		///
		/// \retval GLuint	The amount of vertices.
		///
		////////////////////////////////////////////////////////////
		GLuint getIndexCount(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a vertex to the Mesh object.
		///
		/// \param vertex	The vertex to add to the Mesh.
		///
		////////////////////////////////////////////////////////////
		void addVertex(const Vertex_t& vertex);

		////////////////////////////////////////////////////////////
		/// \brief Adds an index to the Mesh object.
		///
		/// \param index	The index to add to the Mesh.
		///
		////////////////////////////////////////////////////////////
		void addIndex(const GLuint index);

		////////////////////////////////////////////////////////////
		/// \brief Adds a face to the Mesh object.
		///
		/// Convenience method for adding a face to the object. This
		/// method will take in four vertices and calculate the correct
		/// indices accordingly. The order refers to whether the face
		/// is forward-facing.
		///
		/// \param v1		The first vertex of the face.
		/// \param v2		The second vertex of the face.
		/// \param v3		The third vertex of the face.
		/// \param v4		The fourth vertex of the face.
		///	\param order	The rendering order of the face.
		///
		////////////////////////////////////////////////////////////
		void addFace(const Vertex_t& v1, const Vertex_t& v2, const Vertex_t& v3, const Vertex_t& v4, const bool order);

		////////////////////////////////////////////////////////////
		/// \brief Adds a face to the Mesh object.
		///
		/// Convenience method for adding a face to the object. This
		/// method will take in one 2D rectangle and calculate the correct
		/// indices accordingly. The order refers to whether the face
		/// is forward-facing.
		///
		/// \param face		The 2D face to add.
		///	\param order	The rendering order of the face.
		///
		////////////////////////////////////////////////////////////
		void addFace(const Rectf& face, const bool order);

		////////////////////////////////////////////////////////////
		/// \brief Calculate the normals for each Vertex of the Mesh.
		///
		/// If the object does not have, this method can be used to 
		/// generate normals for each Vertex attached to the mesh. This
		/// method can be called manually or within the mesh generate
		/// method.
		///
		////////////////////////////////////////////////////////////
		void calculateNormals(void);

		////////////////////////////////////////////////////////////
		/// \brief Calculate the normals for a specific face of the Mesh.
		///
		/// This can be used to generate the normals of a particular face
		// of the mesh. This is used within the chunk generation algorithm
		/// to create correct normals.
		///
		/// \param start	The starting index of the face.
		/// \param invert	Invert the normals of not.
		///
		////////////////////////////////////////////////////////////
		void calculateFaceNormals(const GLuint start, const bool invert);

		////////////////////////////////////////////////////////////
		/// \brief Clears the vertices and indices of the Mesh object.
		////////////////////////////////////////////////////////////
		void clear(void);

		////////////////////////////////////////////////////////////
		/// \brief Clears the vertices and indices of the Mesh object
		///		   and sets the generated state to false.
		////////////////////////////////////////////////////////////
		void reset(void);

		////////////////////////////////////////////////////////////
		/// \brief Generates the buffers of the Mesh.
		/// 
		/// Before the Mesh can be rendered onto the screen, the OpenGL
		/// buffers must be generated and bound from the vertex and
		/// index information. This allows for communication between the
		/// Mesh and OpenGL.
		///
		///
		////////////////////////////////////////////////////////////
		void generate(const bool genNormals = false);

		////////////////////////////////////////////////////////////
		/// \brief Abstract rendering method for rendering the Mesh.
		///
		/// Abstract method that will be overriden by child classes for
		/// rendering the Mesh. Each Mesh class will have different
		/// rendering methodologies.
		///
		////////////////////////////////////////////////////////////
		virtual void render(void) = 0;
	};

}//namespace sparky

#endif//__SPARKY_IMESH_COMPONENT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::IMeshComponent
/// \ingroup rendering
///
/// sparky::IMeshComponent is the base abstract class for every
/// mesh used within the Sparky Engine. It provides the basic
/// functionality of a Mesh such as manually adding vertices 
/// and indices. 
///
/// For examples on use refer to the MeshData class. 
///
////////////////////////////////////////////////////////////