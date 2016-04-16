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

#ifndef __SPARKY_THREAD_POOL_HPP__
#define __SPARKY_THREAD_POOL_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>				// STL container for all the current threads.
#include <thread>				// Used for multi-threading the application.
#include <mutex>				// Mutually-exclusive. Stops memory from being changed at the same time by locking it.
#include <condition_variable>	// The amount of threads to use, depending on specific conditions.
#include <queue>				// STL container for all of the tasks that the threads have to process.
#include <functional>
#include <future>			    // Packaged tasks. Similar to std::function but can be quickly moved to different threads. Can also
								// retrieve future variables from them, which can be used for getting a return type from a package
								// within a different thread.

namespace sparky
{
	class ThreadPool
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<std::thread>	           m_workers;	// The amount of threads that this Pool will utilise.
		std::queue<std::packaged_task<bool()>> m_tasks;		// The tasks to be processed by the individual threads.

		std::mutex						       m_mutex;		// Stops Data race and memory being changed at the same time.
		std::condition_variable			       m_condition;	// Controls the flow of threads to be utilised by the Pool, depending on parameters.

		bool							       m_stopped;	// Stops after all the threads have joined and finished.

	private:
		/*
		====================
		Private Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Infinitely loops through the tasks within the list.
		///
		/// An infinite loop that operates continuously throughout the application's lifetime. 
		/// When the pool is assigned a task, the pool will locate any threads that are 
		/// currently in-active and assign it the task. The thread will be notified and run this
		/// task. When the task is complete, the thread will go back to sleep until used again. 
		///
		////////////////////////////////////////////////////////////
		void run(void);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs the Thread Pool with a set amount of threads.
		/// 
		/// Default constructor of the Thread Pool object instance. The amount of 
		/// threads that the pool will utilise is set by default to the maximum 
		/// that the hardware can utilise. The user can specify if they wish 
		/// to use less threads for the pool.
		/// 
		/// \param threads	The amount of threads that the pool will utilise.
		///
		////////////////////////////////////////////////////////////
		explicit ThreadPool(const unsigned int threads = std::thread::hardware_concurrency());

		////////////////////////////////////////////////////////////
		/// \brief Destruction of the Thread Pool object.
		/// 
		/// Default destruction of the Thread Pool object instance. This 
		/// will make sure that all of the threads have stopped before 
		/// joining them back to the main thread.
		///
		////////////////////////////////////////////////////////////
		~ThreadPool(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a task that an inactive thread will execute.
		/// 
		/// Adds a task to the queue of tasks that are to be executed by the 
		/// threads within the pool. If no threads are currently available,
		/// it is added to a queue and executed as soon as possible.
		/// 
		/// \param function		The function that the threads will execute.
		///
		/// \retval future		The future result of the added task.
		///
		////////////////////////////////////////////////////////////
		std::future<bool> addTask(const std::function<bool()>& function);

		////////////////////////////////////////////////////////////
		/// \brief Joins each thread back to the main thread.
		///
		/// This method is automatically called upon destruction of the Thread Pool. 
		/// It joins all of the current threads within the pool and sets it stop 
		/// multi-threading.
		/// 
		////////////////////////////////////////////////////////////
		void join(void);
	};

}//namespace sparky

#endif//__SPARKY_THREAD_POOL_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::ThreadPool
/// \ingroup utils
///
/// The Thread Pool is a convenience class for easily setting up multi-threaded 
/// applications and useability without having to over-complicate code bases 
/// and scatter locks. The thread pool will continuously run in the background of 
/// the application and process any tasks assigned to it.
///
/// This is useful for assigning tasks which may slow down certain elements of 
/// the engine, such as the chunk generation for the Voxel World. Below is an
/// example of using the Pool without the Thread Manager.
///
/// \code
/// // Create a pool with the maximum amount of threads.
/// sparky::ThreadPool pool;
/// 
/// // Add a task and store the future result with a lambda
/// int number = 5;
/// std::future<bool> fu = pool.addTask([&number](int num) { return num == 5; });
///
/// // OR add a function called foo and store the result.
/// std::future<bool> fu = pool.addTask(&foo);
///
/// // Print the result of the task
/// std::cout << fu.get() << std::endl;
///
/// // Join the pool to the main thread.
/// pool.join();
///
////////////////////////////////////////////////////////////
