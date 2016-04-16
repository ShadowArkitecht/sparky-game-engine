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
#include <sparky\core\object.hpp>	// Objects need to be released upon flushing the current pool.

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
	void PoolManager::addObject(Object* pObject)
	{
		m_objects.push_back(pObject);
	}

	////////////////////////////////////////////////////////////
	bool PoolManager::contains(Object* pObject) const
	{
		return std::find(m_objects.begin(), m_objects.end(), pObject) != m_objects.end();
	}

	////////////////////////////////////////////////////////////
	void PoolManager::flush(void)
	{
		if (!m_objects.empty())
		{
			std::vector<Object*> releases;
			releases.swap(m_objects);

			for (auto& r : releases)
			{
				Object::release(r);
			}

			releases.clear();
		}
	}

}//namespace sparky