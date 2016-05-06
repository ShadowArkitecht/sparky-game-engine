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
#include <sparky\math\transform.hpp>	// The position, scale and rotation of the Chunk object.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class MeshData;
	class IShaderComponent;

	class Chunk : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		static const int		SIZE;			// The standard size of all Chunks.
		Transform				m_transform;	// The transform of the Chunk.
		std::array<Voxel, 4096> m_voxels;		// The individual voxels of the chunk.
		MeshData*				m_pMesh;	    // The mesh that renders the voxels.
		bool					m_shouldLoad;	// Whether the current chunk object needs to generate.

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
		static int getSize(void);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the Transform of the Chunk object.
		///
		/// \retval Transform	The transform of the Chunk object.
		///
		////////////////////////////////////////////////////////////
		Transform& getTransform(void);

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
		void render(IShaderComponent* pShader);
	};

}//namespace sparky

#endif//__SPARKY_CHUNK_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Chunk
/// \ingroup generation
///
/// sparky::Chunk is a collection of 16 * 16 * 16 voxels which 
/// are grouped together into a single draw call. Chunking the
/// voxels together significantly improves the frame-rate of 
/// the application.
///
/// The voxels of the chunk can be updated by directly accessing
/// the individual elements of the chunk. Below is a code example.
///
/// \code
/// // Create a chunk object.
/// sparky::Chunk* pChunk = new sparky::Chunk();
///
/// // Change a voxel within the chunk.
/// pChunk->getVoxel(0, 0, 0).setActive(false);
///
/// // Add the chunk greedy meshing to a seperate thread.
/// sparky::ThreadManager::getInstance().addTask(std::bind(&sparky::Chunk::greedy, pChunk));
///
/// // Render the chunk.
/// pChunk->render(sparky::ResourceManager::getInstance().getShader("basic"));
///
////////////////////////////////////////////////////////////