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
#include <sparky\core\iobject.hpp>		// Chunk is a type of Object within the engine.
#include <sparky\generation\Voxel.hpp>	// Voxels make up the Chunk itself.
#include <sparky\math\transform.hpp>	// The position, scale and rotation of the Chunk object.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class MeshData;
	class World;

	enum eFaceDirection
	{
		FACE_WEST,
		FACE_EAST,
		FACE_SOUTH,
		FACE_NORTH,
		FACE_FORWARD,
		FACE_BACKWARD,
		MAX_FACES
	};

	class Chunk : public IObject
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		static const int		m_sSize;		///< The standard size of all Chunks.
		std::array<Voxel, 4096> m_voxels;		///< The individual voxels of the Chunk.
		MeshData*				m_pMesh;	    ///< The mesh that renders the voxels.
		World*					m_pWorld;		///< World object that this chunk is attached to.
		bool					m_isActive;		///< If the Chunk has any voxels its needs to render.
		std::array<Chunk*, 6>   m_neighbours;	///< The neighbouring chunks of the Chunk.

		std::array<bool, 6>		m_checks;		///< The adjacent checks of the voxel.
		bool					m_shouldLoad;	///< Whether the current Chunk object needs to generate.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Checks the adjacent neighbours of the Voxel.
		///
		/// The neighbours of the current Voxel are checked for their current
		/// activity, if the chunks are active on all sides, there is no reason
		/// for this voxel to render.
		///
		/// \param pos	The position of the Voxel to check.
		///
		////////////////////////////////////////////////////////////
		void checkNeighbours(const Vector3i& pos);

		////////////////////////////////////////////////////////////
		/// \brief Adds geometry at the desired position whilst checking the
		///        activity of neighbours.
		///
		/// \param pos	The position to add the geometry to.
		///
		////////////////////////////////////////////////////////////
		void addToMesh(const Vector3i& pos);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Chunk object.
		///
		/// When the Chunk is instantiated, the Mesh is dynamically
		/// allocated and retained for use.
		///
		////////////////////////////////////////////////////////////
		explicit Chunk(void);

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Chunk object.
		///
		/// When the object is destroyed, the MeshData is de-allocated and 
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
		/// \brief Retrieves the uniform dimensions of the Chunk.
		///
		/// \retval int		The size of the Chunk object.
		///
		////////////////////////////////////////////////////////////
		static int getSize(void);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a reference to the Voxel at the position specified.
		/// 
		/// \param pos		The position of the Voxel.
		///
		/// \retval Voxel	The Voxel at the specified position.
		///
		////////////////////////////////////////////////////////////
		Voxel* getVoxel(const Vector3i& pos);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a reference to the Voxel at the position specified.
		/// 
		/// \param x		The x position of the Voxel.
		/// \param y		The y position of the Voxel.
		/// \param z		The z position of the Voxel.
		///
		/// \retval Voxel*	The Voxel at the specified position.
		///
		////////////////////////////////////////////////////////////
		Voxel* getVoxel(const int x, const int y, const int z);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the underlying MeshData of the Chunk.
		/// 
		/// \retval MeshData	The MeshData of the Chunk.
		///
		////////////////////////////////////////////////////////////
		MeshData* getMesh(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the World object of the Chunk.
		///
		/// When a chunk is created, it is attached to a World object. 
		/// If a voxel if achieved from the chunk and is out of scope,
		/// it will search the world object.
		///
		/// \param pWorld	The World parent of the Chunk.
		///
		////////////////////////////////////////////////////////////
		void setWorld(World* pWorld);

		Chunk* getNeighbour(eFaceDirection direction) const;

		void setNeighbour(eFaceDirection direction, Chunk* pChunk);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Performs culling on the current Chunk object.
		///
		/// When the current Chunk is culled, it only created vertices and
		/// geometry for the voxels that can be directly seen.
		///
		////////////////////////////////////////////////////////////
		void culled(void);

		////////////////////////////////////////////////////////////
		/// \brief Reduces the amount of vertices that a Chunk contains.
		///
		/// Greedy meshing checks each Voxel and its adjacent neighbours,
		/// if the Chunk is active and the materials match, the faces will
		/// be merged. Greedy meshing helps to reduce the amount of 
		/// memory that each Chunk contains.
		///
		////////////////////////////////////////////////////////////
		void greedy(void);

		////////////////////////////////////////////////////////////
		/// \brief Clears the Chunk MeshData of all vertices and indices.
		////////////////////////////////////////////////////////////
		void reset(void);

		////////////////////////////////////////////////////////////
		/// \brief Updates the current Chunk object.
		///
		/// When the chunk is updated, it will check if it needs to
		/// become active or needs to be generated.
		///
		////////////////////////////////////////////////////////////
		void update(void) override;

		////////////////////////////////////////////////////////////
		/// \brief Renders the current Chunk object.
		///
		/// The Chunk will only render if it is currently active within
		/// the application and within the camera's frustum.
		///
		/// \param pShader	The shader to render the Chunk with.
		///
		////////////////////////////////////////////////////////////
		void render(IShaderComponent* pShader) override;
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
/// The voxels of the Chunk can be updated by directly accessing
/// the individual elements of the Chunk. Below is a code example.
///
/// Usage example:
/// \code
/// // Create a Chunk object and retain it.
/// sparky::Chunk* pChunk = new sparky::Chunk();
/// pChunk->addRef();
///
/// // Change a Voxel within the Chunk.
/// pChunk->getVoxel(0, 0, 0).setActive(false);
///
/// // Add the Chunk greedy meshing to a seperate thread.
/// sparky::ThreadManager::getInstance().addTask(std::bind(&sparky::Chunk::greedy, pChunk));
///
/// // Render the Chunk.
/// pChunk->render(sparky::ResourceManager::getInstance().getShader("deferred"));
/// \endcode
///
////////////////////////////////////////////////////////////