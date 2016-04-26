#include <sparky\utils\threadmanager.hpp>

namespace sparky
{
	ThreadManager::ThreadManager(void)
		: Singleton<ThreadManager>(), m_pool()
	{
	}

	ThreadManager::~ThreadManager(void)
	{
		m_pool.join();
	}

	void ThreadManager::addTask(const std::function<void()>& function)
	{
		m_pool.addTask(function);
	}

}//namespace sparky