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

#ifndef __SPARKY_VOXEL_HPP__
#define __SPARKY_VOXEL_HPP__

namespace sparky
{
	/*
	====================
	Enumerations
	====================
	*/
	enum class eVoxelType
	{
		DIRT,
		STONE
	};

	class Voxel
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		eVoxelType m_type;		// The voxel type i.e Water, Dirt, Stone.
		bool	   m_active;	// Whether the current voxel is active.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of a Voxel object.
		///
		/// The default construction of a voxel will set its activity
		/// to true and it's type to dirt.
		///
		////////////////////////////////////////////////////////////
		explicit Voxel(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Voxel object.
		////////////////////////////////////////////////////////////
		~Voxel(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the type of the Voxel object.
		///
		/// The type refers to the texture that the chunk will render
		/// with and it's specific behaviours within the world.
		///
		/// \retval eVoxelType	The type of voxel.
		///
		////////////////////////////////////////////////////////////
		eVoxelType getType(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Set the type of the Voxel object.
		///
		/// The type refers to the texture that the chunk will render
		/// with and it's specific behaviours within the world.
		///
		////////////////////////////////////////////////////////////
		void setType(const eVoxelType type);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the activity of the current Voxel object.
		///
		/// The activity of the Voxel specifies whether the current Voxel
		/// will render within it's chunk.
		///
		/// \retval bool	The activity of the Voxel object.
		///
		////////////////////////////////////////////////////////////
		bool isActive(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the activity of the current Voxel object.
		///
		/// The activity of the Voxel specifies whether the current Voxel
		/// will render within it's chunk.
		///
		////////////////////////////////////////////////////////////
		void setActive(const bool active);
	};

}//namespace sparky

#endif//__SPARKY_VOXEL_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Voxel
/// \ingroup generation
///
/// sparky::Voxel is the lowest level element of the Voxel aspect
/// of the engine. A Voxel is used to represent a 3D position in
/// space, that is rendered as a cube. The memory footprint of the 
/// voxel must be low therefore it only contains information about
/// it's activity and the type.
///
/// Voxels are never created by the user, they are allocated when
/// a Chunk object is created within the application. Individual
/// voxels can be accessed through the Chunk object. Below is a code
/// example.
///
/// \code
/// // Create a Chunk object and adds its meshing to the threading list.
/// sparky::Chunk* pChunk = new sparky::Chunk();
/// pChunk->addRef();
///
/// sparky::ThreadManager::getInstance().addTask(std::bind(&Chunk::greedy, pChunk));
///
/// // Store the information of a voxel from within the chunk.
/// sparky::Voxel voxel = pChunk->getVoxel(0, 0, 0);
///
/// // Print the information about the voxel.
/// std::cout << voxel.getType() << std::endl;
/// std::cout << voxel.isActive() << std::endl;
///
////////////////////////////////////////////////////////////