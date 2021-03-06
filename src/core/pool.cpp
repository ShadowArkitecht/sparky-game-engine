/*
====================
CPP Includes
====================
*/
#include <algorithm>				// Finding objects within a vector without a for-loop.
/*
====================
Class Includes
====================
*/
#include <sparky\core\pool.hpp>		// Class definition.
#include <sparky\core\ref.hpp>		// Objects need to be released upon flushing the current pool.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	PoolManager::PoolManager(void)
		: Singleton<PoolManager>(), m_objects()
	{
	}

	////////////////////////////////////////////////////////////
	PoolManager::~PoolManager(void)
	{
		this->flush();
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void PoolManager::addObject(Ref* pObject)
	{
		m_objects.push_back(pObject);
	}

	////////////////////////////////////////////////////////////
	bool PoolManager::contains(Ref* pObject) const
	{
		return std::find(std::begin(m_objects), std::end(m_objects), pObject) != std::end(m_objects);
	}

	////////////////////////////////////////////////////////////
	void PoolManager::flush(void)
	{
		if (!m_objects.empty())
		{
			std::vector<Ref*> releases;
			releases.swap(m_objects);

			for (auto& r : releases)
			{
				Ref::release(r);
			}

			releases.clear();
		}
	}

}//namespace sparky