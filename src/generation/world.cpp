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

/*
====================
Class Includes
====================
*/
#include <sparky\generation\world.hpp>		// Class definition.
#include <sparky\generation\chunk.hpp>		// World is made of chunks.
#include <sparky\rendering\ishader.hpp>		// All of the chunks within the World is rendered with one shader.
#include <sparky\utils\threadmanager.hpp>	// The chunk generation is multi-threaded for quicker execution.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	World::World(void)
		: m_chunks()
	{
	}

	////////////////////////////////////////////////////////////
	World::~World(void)
	{
		for (auto& chunk : m_chunks)
		{
			Ref::release(chunk.second);
		}

		m_chunks.clear();
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	Chunk* World::getChunk(const Vector3i& pos) const
	{
		return this->getChunk(pos.x, pos.y, pos.z);
	}

	////////////////////////////////////////////////////////////
	Chunk* World::getChunk(const int x, const int y, const int z) const
	{
		Vector3i size(Chunk::getSize(), Chunk::getSize(), Chunk::getSize());
		Vector3i position;

		position.x = (x / size.x) * size.x;
		position.y = (y / size.y) * size.y;
		position.z = (z / size.z) * size.z;

		auto chunk = m_chunks.find(position);

		if (chunk != m_chunks.end())
		{
			return chunk->second;
		}

		return nullptr;
	}

	////////////////////////////////////////////////////////////
	Voxel* World::getVoxel(const Vector3i& pos)
	{
		return this->getVoxel(pos.x, pos.y, pos.z);
	}

	////////////////////////////////////////////////////////////
	Voxel* World::getVoxel(const int x, const int y, const int z)
	{
		Chunk* pChunk = this->getChunk(x, y, z);

		if (pChunk)
		{
			Vector3i diff(pChunk->getTransform().getPosition());
			return pChunk->getVoxel(x - diff.x, y - diff.y, z - diff.z);
		}

		return nullptr;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void World::addChunk(const Vector3i& pos)
	{
		auto itr = m_chunks.find(pos);

		if (itr == m_chunks.end())
		{
			Chunk* pChunk = new Chunk();
			pChunk->getTransform().setPosition(Vector3f(pos));
			
			pChunk->setWorld(this);

			pChunk->addRef();

			m_chunks.insert(std::make_pair(pos, pChunk));
		}
	}

	////////////////////////////////////////////////////////////
	void World::build(eMeshingType type)
	{
		for (auto& chunk : m_chunks)
		{
			switch (type)
			{
			case eMeshingType::CULLED:
				ThreadManager::getInstance().addTask(std::bind(&Chunk::culled, chunk.second));
				break;

			case eMeshingType::GREEDY:
				ThreadManager::getInstance().addTask(std::bind(&Chunk::greedy, chunk.second));
				break;
			}
		}
	}

	////////////////////////////////////////////////////////////
	void World::update(void)
	{
		for (const auto& chunk : m_chunks)
		{
			chunk.second->update();
		}
	}

	////////////////////////////////////////////////////////////
	void World::render(IShaderComponent* pShader)
	{
		for (const auto& chunk : m_chunks)
		{
			pShader->update(chunk.second->getTransform());
			chunk.second->render(pShader);
		}
	}

}//namespace sparky