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
		std::array<Voxel, 16 * 16 * 16>	  m_voxels;	// The individual voxels of the chunk.
		MeshData*				          m_pMesh;	// The mesh that renders the voxels.

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
		////////////////////////////////////////////////////////////
		Voxel& getVoxel(const Vector3i& pos);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a reference to the voxel at the position.
		/// 
		/// \param x	The x position of the voxel.
		/// \param y	The y position of the voxel.
		/// \param z	The z position of the voxel.
		///
		////////////////////////////////////////////////////////////
		Voxel& getVoxel(const int x, const int y, const int z);

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