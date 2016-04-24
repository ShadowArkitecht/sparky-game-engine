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

#ifndef __SPARKY_CHUNK_HPP__
#define __SPARKY_CHUNK_HPP__

/*
====================
CPP Includes
====================
*/
#include <array>						// Storage type for voxels.

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>			// Chunk is a dynamically allocated object.
#include <sparky\generation\voxel.hpp>	// Voxels make up the Chunk itself.
#include <sparky\math\vector3.hpp>		// 3 dimensional array accessor.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class MeshData;

	class Chunk : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::array<Voxel, 16 * 16 * 16> m_voxels;		// The individual voxels of the chunk.
		MeshData*				        m_pMesh;	    // The mesh that renders the voxels.
		bool					        m_shouldLoad;

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Chunk object.
		///
		/// When the chunk is instantiated, the Mesh is dynamically
		/// allocated and retained for use.
		///
		////////////////////////////////////////////////////////////
		explicit Chunk(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Chunk object.
		///
		/// When the object is destroyed, the Mesh is de-allocated and 
		/// and the memory is released for other use.
		///
		////////////////////////////////////////////////////////////
		~Chunk(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves a reference to the voxel at the position.
		/// 
		/// \param pos		The position of the voxel.
		///
		/// \retval Voxel	The voxel at the specified position.
		///
		////////////////////////////////////////////////////////////
		Voxel& getVoxel(const Vector3i& pos);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a reference to the voxel at the position.
		/// 
		/// \param x		The x position of the voxel.
		/// \param y		The y position of the voxel.
		/// \param z		The z position of the voxel.
		///
		/// \retval Voxel	The voxel at the specified position.
		///
		////////////////////////////////////////////////////////////
		Voxel& getVoxel(const int x, const int y, const int z);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the underlying mesh data of the Chunk.
		/// 
		/// \retval MeshData	The mesh of the Chunk.
		///
		////////////////////////////////////////////////////////////
		MeshData* getMesh(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Reduces the amount of vertices that a chunk contains.
		///
		/// Greedy meshing checks each voxel and its adjacent neighbours,
		/// if the chunk is active and the materials match, the faces will
		/// be merged. Greedy meshing helps to reduce the amount of 
		/// memory that each chunk contains.
		///
		////////////////////////////////////////////////////////////
		void greedy(void);

		////////////////////////////////////////////////////////////
		/// \brief Clears the Chunk mesh of all vertices and indices.
		////////////////////////////////////////////////////////////
		void reset(void);

		////////////////////////////////////////////////////////////
		/// \brief Renders the Chunk object to the buffer.
		////////////////////////////////////////////////////////////
		void render(void);
	};

}//namespace sparky

#endif//__SPARKY_CHUNK_HPP__