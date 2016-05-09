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
		/*
		====================
		Member Variables
		====================
		*/
		ThreadPool m_pool;	///< The underlying Thread Pool of the ThreadManager.

	private:
		/*
		====================
		Private Ctor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default private construction of the ThreadManager 
		///		   class.
		///
		/// This constructor will call the behaviour of it's parent
		/// constructor and initialise the thread pool with the
		/// maximum amount of available threads.
		///
		////////////////////////////////////////////////////////////
		explicit ThreadManager(void);

	public:
		/*
		====================
		Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Destruction of the ThreadManager object.
		///
		/// The destructor will join all of the currently active threads
		/// back to the main thread before de-allocation.
		///
		////////////////////////////////////////////////////////////
		~ThreadManager(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a task to the thread pool for execution.
		///
		/// A task can be any function or method pointer in which
		/// void is specified as its return type. The function pointer
		/// allows for completely modular behaviour and tasks to be
		/// added to the task queue.
		///
		/// \param function		The function to execute on the threads.
		///
		////////////////////////////////////////////////////////////
		void addTask(const std::function<void()>& function);
	};

}//namespace sparky

#endif//__SPARKY_THREAD_MANAGER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::ThreadManager
/// \ingroup utils
/// 
/// sparky::ThreadManager is a singleton class which allows
/// for global access to the applications thread pool. This
/// global access allows for any function or method within the
/// application to be multi-threaded and executed on a seperate
/// thread.
///
/// sparky::ThreadManager is a global wrapper class for the thread
/// pool. Below is a code example of using the Thread Manager.
///
/// Usage example:
/// \code 
/// // Create a void function which just prints a statement.
/// void printSentence(void)
/// {
///		std::cout << "Multi-threaded function!" << std::endl;
/// }
///
/// Adds the function to the thread manager.
/// sparky::ThreadManager::getInstance().addTask(printSentence);
/// \endcode
///
////////////////////////////////////////////////////////////