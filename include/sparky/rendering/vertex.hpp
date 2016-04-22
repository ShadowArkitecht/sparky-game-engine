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

#ifndef __SPARKY_VERTEX_HPP__
#define __SPARKY_VERTEX_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\math\vector3.hpp>	// Stores the position of the Vertex.
#include <sparky\math\vector2.hpp>	// Stores the uv / texture co-ordinate of the Vertex.

namespace sparky
{
	struct Vertex_t
	{
		/*
		====================
		Member Variables
		====================
		*/
		Vector3f position;		// Position of the Vertex in 3D space.
		Vector3f normal;		// The normal of the vertex.
		Vector2f uv;			// The texture co-ordinate of the Vertex.

		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of a Vertex object.
		///
		/// Sets the position and uv values of the Vertex object to 
		/// default values - [ 0, 0, 0 ], [ 0, 0 ].
		///
		////////////////////////////////////////////////////////////
		explicit Vertex_t(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Vertex object with a position and uv.
		///
		/// Implicity sets the attributes of the Vertex object by
		/// constructing a Vertex from the parameter values.
		///
		/// \param position		The positon of the Vertex in 3D space.
		/// \param uv			The texture co-ordinates of the Vertex.
		///
		////////////////////////////////////////////////////////////
		explicit Vertex_t(const Vector3f& position, const Vector2f& uv);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Vertex object with a position, normal and uv.
		///
		/// Implicity sets the attributes of the Vertex object by
		/// constructing a Vertex from the parameter values.
		///
		/// \param position		The positon of the Vertex in 3D space.
		/// \param normal		The normals of the Vertex.
		/// \param uv			The texture co-ordinates of the Vertex.
		///
		////////////////////////////////////////////////////////////
		explicit Vertex_t(const Vector3f& position, const Vector3f& normal, const Vector2f& uv);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Vertex object.
		////////////////////////////////////////////////////////////
		~Vertex_t(void) = default;
	};

}//namespace sparky

#endif//__SPARKY_VERTEX_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Vertex_t
/// \ingroup rendering
///
/// sparky::Vertex_t is a structure that contains the information
/// of a Vertex. A vertex is a single position in 3D space that
/// contains information about it's position, texture co-ordinates
/// and normals.
///
/// Models and meshes are constructed from several vertices which
/// defines their shapes and textures. Below is code example of adding
/// a vertex to a mesh.
///
/// // Create a new mesh and increase its reference count.
/// sparky::MeshData* pMesh = new MeshData();
/// pMesh->addRef();
///
/// // Create a vertex and add it to the mesh.
/// sparky::Vertex_t vertex(Vector3f::zero(), Vector2f::one());
/// pMesh->addVertex(vertex);
///
////////////////////////////////////////////////////////////