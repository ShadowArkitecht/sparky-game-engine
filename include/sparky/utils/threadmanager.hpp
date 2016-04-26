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

#ifndef __SPARKY_THREAD_MANAGER_HPP__
#define __SPARKY_THREAD_MANAGER_HPP__

#include <sparky\utils\singleton.hpp>
#include <sparky\utils\threadpool.hpp>

namespace sparky
{
	class ThreadManager final : public Singleton<ThreadManager>
	{
		friend class Singleton<ThreadManager>;

	private:
		ThreadPool m_pool;

	private:
		explicit ThreadManager(void);

	public:
		~ThreadManager(void);
		void addTask(const std::function<void()>& function);
	};

}//namespace sparky

#endif//__SPARKY_THREAD_MANAGER_HPP__