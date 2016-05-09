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

#ifndef __SPARKY_MESH_DATA_HPP__
#define __SPARKY_MESH_DATA_HPP__

/*
====================
CPP Includes
====================
*/
#include <sparky\rendering\imesh.hpp>	// Inherits from IMeshComponent.

namespace sparky
{
	class MeshData : public IMeshComponent
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default MeshData object construction. Inherits 
		///		   IMeshComponent constructor.
		////////////////////////////////////////////////////////////
		explicit MeshData(void);

		////////////////////////////////////////////////////////////
		/// \brief Default MeshData object destruction.
		////////////////////////////////////////////////////////////
		~MeshData(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Renders the MeshData to the Window.
		///
		/// The indices of the Mesh are read and drawn to the screen
		/// by using glDrawElements.
		///
		////////////////////////////////////////////////////////////
		void render(void) override;
	};

}//namespace sparky

#endif//__SPARKY_MESH_DATA_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::MeshData
/// \ingroup rendering
///
/// sparky::MeshData is a child class of IMeshComponent which
/// is used to manually define the vertices and indices of a 
/// Mesh. If the user wants to create basic shapes within the
/// source code, sparky::MeshData should be utilised.
///
/// Before the MeshData can be rendered, it must be generated
/// for use. Below is a code example to make a basic square 
/// on-screen.
///
/// Usage example:
/// \code
/// // Create a config file and load it from external source.
/// sparky::ConfigFile config;
/// config.open("data/config.scfg");
///
/// // Create a window with the information from the config file.
/// sparky::Window window;
/// window.create(config);
///
/// // Make a mesh and add a face of vertices.
/// sparky::MeshData* pMesh = new sparky::MeshData();
///
/// sparky::Vertex_t v1(sparky::Vector3f(-0.5f, -0.5f, 0.0f), sparky::Vector2f(0.0f, 0.0f));
/// sparky::Vertex_t v2(sparky::Vector3f( 0.5f, -0.5f, 0.0f), sparky::Vector2f(1.0f, 0.0f));
/// sparky::Vertex_t v3(sparky::Vector3f( 0.5f,  0.5f, 0.0f), sparky::Vector2f(1.0f, 1.0f));
/// sparky::Vertex_t v4(sparky::Vector3f(-0.5f,  0.5f, 0.0f), sparky::Vector2f(0.0f, 1.0f));
///
/// pMesh->addFace(v1, v2, v3, v4, 0);
///
/// // Generate the Mesh.
/// pMesh->generate();
///
/// // Basic rendering loop.
/// while (window.isRunning())
/// {
///		window.clear();
///		// Render the mesh.
///		pMesh->render();
///
///		window.swap();
/// }
/// \endcode
///
////////////////////////////////////////////////////////////