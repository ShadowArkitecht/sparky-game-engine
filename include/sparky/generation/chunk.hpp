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
		std::array<Voxel, 27>	  m_voxels;	// The individual voxels of the chunk.
		MeshData*				  m_pMesh;	// The mesh that renders the voxels.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit Chunk(void);
		~Chunk(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		Voxel& getVoxel(const Vector3i& pos);
		Voxel& getVoxel(const int x, const int y, const int z);

		/*
		====================
		Methods
		====================
		*/
		void greedy(void);
		void reset(void);
		void render(void);
	};

}//namespace sparky

#endif//__SPARKY_CHUNK_HPP__