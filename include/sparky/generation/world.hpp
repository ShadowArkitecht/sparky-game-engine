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

#ifndef __SPARKY_WORLD_HPP__
#define __SPARKY_WORLD_HPP__

/*
====================
CPP Includes
====================
*/
#include <map>						// The container for the chunks.
/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>		// World is a dynamically allocated object.
#include <sparky\math\vector3.hpp>	// The position of the chunk in world position.

namespace sparky
{
	/*
	====================
	Enumerations
	====================
	*/
	enum class eMeshingType
	{
		CULLED,
		GREEDY
	};

	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class Chunk;
	class Voxel;
	class IShaderComponent;

	class Comparer
	{
	public:
		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Functor for getting the difference between two different
		///	       Vector3 values.
		///
		/// \param u		The first Vector3 to compare.
		/// \param v		The second Vector3 to compare.
		///
		/// \retval bool	True if the Vector3 objects match.
		///
		////////////////////////////////////////////////////////////
		bool operator()(const Vector3i& u, const Vector3i& v) const
		{
			return u.x < v.x || (u.x == v.x && (u.y < v.y || (u.y == v.y && u.z < v.z)));
		}
	};

	class World final : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::map<Vector3i, Chunk*, Comparer> m_chunks;	///< All the chunks within the World.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the World object. Sets all
		///        the member variables to default values.
		////////////////////////////////////////////////////////////
		explicit World(void);

		////////////////////////////////////////////////////////////
		/// \brief Destructor of the World object.
		/// 
		/// When the World object is destroyed. All of the retained
		/// Chunk objects are de-allocated and destroyed.
		///
		////////////////////////////////////////////////////////////
		~World(void);

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves a Chunk object from the World at the specified position.
		///
		/// \param pos	The position of the Chunk to retrieve.
		///
		/// \retval Chunk*	A pointer to the Chunk at the specified position.
		///
		////////////////////////////////////////////////////////////
		Chunk* getChunk(const Vector3i& pos) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a Chunk object from the World at the specified position.
		///
		/// \param x	The x position of the Chunk to retrieve.
		/// \param y	The y position of the Chunk to retrieve.
		/// \param z	The z position of the Chunk to retrieve.
		///
		/// \retval Chunk*	A pointer to the Chunk at the specified position.
		///
		////////////////////////////////////////////////////////////
		Chunk* getChunk(const int x, const int y, const int z) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a Voxel at the desired position.
		///
		/// The Voxel will be retrieved from the world at the correct 
		/// Chunk instance. If the voxel does not exist, the method will
		/// return a nulllptr.
		///
		/// \param pos	The 3D position of the Voxel.
		///
		/// \retval	Voxel*	A pointer to the Voxel at the specified position.
		///
		////////////////////////////////////////////////////////////
		Voxel* getVoxel(const Vector3i& pos);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves a Voxel at the desired position.
		///
		/// The Voxel will be retrieved from the world at the correct 
		/// Chunk instance. If the voxel does not exist, the method will
		/// return a nulllptr.
		///
		/// \param x	The x position of the Voxel.
		/// \param y	The y position of the Voxel.
		/// \param z	The z position of the Voxel.
		///
		/// \retval	Voxel*	A pointer to the Voxel at the specified position.
		///
		////////////////////////////////////////////////////////////
		Voxel* getVoxel(const int x, const int y, const int z);

		////////////////////////////////////////////////////////////
		/// \brief Add a Chunk to the World at the specified position.
		///
		/// When a Chunk needs to be added to the World, it will check if
		/// a Chunk has already been created at this location. If there has not,
		/// a new Chunk is created and added to the map.
		///
		/// \param pos	The position to place the new Chunk.
		///
		////////////////////////////////////////////////////////////
		void addChunk(const Vector3i& pos);

		////////////////////////////////////////////////////////////
		/// \brief Builds all of the current Chunks contained within the World.
		///
		/// When a Chunk object is added to the World, unless specified the
		/// Chunk has not been constructed. Therefore this method will utilised
		/// multi-threading to build all of the different chunks.
		///
		/// \param type		The type of meshing algorithm to use.
		///
		////////////////////////////////////////////////////////////
		void build(eMeshingType type);

		////////////////////////////////////////////////////////////
		/// \brief Updates all of the Chunks within the World.
		////////////////////////////////////////////////////////////
		void update(void);

		////////////////////////////////////////////////////////////
		/// \brief Renders all of the Chunks within the World.
		///
		/// \param pShader	The shader to render the World with.
		///
		////////////////////////////////////////////////////////////
		void render(IShaderComponent* pShader);
	};

}//namespace sparky

#endif//__SPARKY_WORLD_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::World
/// \ingroup generation
///
/// sparky::World is the culmination of all the Chunk's and Voxels
/// within the application in one class. The World controls the
/// rendering and initialisation of Chunk objects.
///
/// Chunks can be added and removed from the World and edited through
/// various convenience methods. Below is a code example of using the World.
///
/// Usage example:
/// \code
/// // Create a new World and retain!
/// sparky::World* pWorld = new sparky::World();
/// pWorld->addRef();
///
/// // Add a Chunk to the World.
/// pWorld->addChunk(sparky::Vector3i::zero());
///
/// // Render the World!
/// pWorld->render(sparky::ResourceManager::getInstance().getShader("deferred"));
/// \endcode
///
////////////////////////////////////////////////////////////