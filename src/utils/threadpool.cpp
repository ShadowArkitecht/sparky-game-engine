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
#include <sparky\utils\threadpool.hpp>	// Class definition.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	ThreadPool::ThreadPool(const unsigned int threads)
		: m_stopped(false)
	{
		for (unsigned int i = 0; i < threads; i++)
		{
			m_workers.emplace_back(std::thread(&ThreadPool::run, this));
		}
	}

	////////////////////////////////////////////////////////////
	ThreadPool::~ThreadPool(void)
	{
		if (!m_stopped)
		{
			join();
		}
	}

	/*
	====================
	Private Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void ThreadPool::run(void)
	{
		std::function<void()> task;

		while (true)
		{
			std::unique_lock<std::mutex> guard(m_mutex);

			m_condition.wait(guard, [this]{ return !m_tasks.empty(); });

			if (m_tasks.empty())
			{
				return;
			}

			task = std::move(m_tasks.front());

			m_tasks.pop();
			guard.unlock();

			task();
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void ThreadPool::addTask(const std::function<void()>& function)
	{
		std::unique_lock<std::mutex> guard(m_mutex);
		m_tasks.push(std::move(function));

		guard.unlock();

		m_condition.notify_one();
	}

	////////////////////////////////////////////////////////////
	void ThreadPool::join(void)
	{
		m_condition.notify_all();

		for (auto& worker : m_workers)
		{
			worker.join();
		}

		m_stopped = true;
	}

}//namespace sparky