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
	Sparky Forward Declarations
	====================
	*/
	class Chunk;
	class Voxel;
	class IShaderComponent;

	class Comparer
	{
	public:
		bool operator()(const Vector3i& u, const Vector3i& v) const
		{
			return u.x < v.x || (u.x == v.x && (u.y < v.y || (u.y == v.y && u.z < v.z)));
		}
	};

	class World final : public Ref
	{
	private:
		std::map<Vector3i, Chunk*, Comparer> m_chunks;

	public:
		explicit World(void);
		~World(void);

		Chunk* getChunk(const Vector3i& pos) const;
		Chunk* getChunk(const int x, const int y, const int z) const;

		//Voxel& getVoxel(const Vector3i& pos);
		//Voxel& getVoxel(const int x, const int y, const int z) const;

		void addChunk(const Vector3i& pos);
		void render(IShaderComponent* pShader);
	};

}//namespace sparky

#endif//__SPARKY_WORLD_HPP__