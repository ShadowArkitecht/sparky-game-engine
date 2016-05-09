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

#ifndef __SPARKY_POOL_MANAGER_HPP__
#define __SPARKY_POOL_MANAGER_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>						// Container for all of the objects currently retained by the pool.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\singleton.hpp>	// PoolManager is a singleton, therefore it inherits from the Singleton class.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class Ref;

	class PoolManager : public Singleton<PoolManager>
	{
		friend class Singleton<PoolManager>;

	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<Ref*> m_objects;		///< Currently retained dynamic objects.

	private:
		/*
		====================
		Private Ctor
		====================
		*/
		////////////////////////////////////////////////////////////
		///	\brief Constructs a PoolManager object instance. 
		///
		///	Default construction of the PoolManager, it sets all the
		/// member variables to default values. 
		/// 
		////////////////////////////////////////////////////////////
		explicit PoolManager(void);

	public:
		/*
		====================
		Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Destructs the PoolManager object instance.
		///
		/// The flush method is called once more upon the objects
		/// destruction to make sure that it is not retaining any objects,
		/// therefore preventing memory leaks.
		///
		////////////////////////////////////////////////////////////
		~PoolManager(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a dynamic object Ref to the pool.
		///
		/// The object added is retained within the pool until the 
		/// end of the current frame, where the objects reference
		/// count is decremented and cleared from the pool.
		///
		/// \param pObject	The Ref to add to the pool.
		///
		////////////////////////////////////////////////////////////
		void addObject(Ref* pObject);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see if the passed in object is currently within the pool.
		///
		/// This method will search through all of the objects within
		/// the current pool and return true if the object parameter
		/// has been found.
		///
		/// \param pObject	The Ref to search the pool for.
		///
		/// \retval	bool	True if the Ref has been found, false if not.
		///
		////////////////////////////////////////////////////////////
		bool contains(Ref* pObject) const;

		////////////////////////////////////////////////////////////
		/// \brief Flushes the pool of all currently retained Ref's.
		///
		/// At the end of each frame, the pool is emptied of all 
		/// retained Ref's, each Ref's reference counter is decremented
		/// before flushing.
		///
		////////////////////////////////////////////////////////////
		void flush(void);
	};

}//namespace sparky

////////////////////////////////////////////////////////////
/// \class sparky::PoolManager
/// \ingroup core
///
/// sparky::PoolManager is a singleton class that is responsible 
/// for the basic garbage collection of Sparky. Dynamic Ref objects 
/// are added to the list. At the end of the current frame, each 
/// objects reference count is decremented and if the count is 0, 
/// it is deleted. 

/// After every Ref object has been checked, the object pool is cleared. 
/// The only Ref objects left after the flushing are objects that are 
/// referenced by other classes, and therefore their lifetime
/// is tied to that subsequent instance. Below is a small example
/// of the pool in use.
///
/// Usage example:
/// \code
/// // Creating a Window.
/// sparky::Window window;
/// window.create("Sparky!", Vector2i(), Vector2i(640, 480));
///
/// // Creating an Ref.
/// sparky::Ref* pObject = new sparky::Ref();
///
/// // Basic game loop.
/// while (window.isRunning())
/// {
///		window.clear();
///		// Render objects.
///		window.swap();
///		//Empty the pool at the end of the frame.
///		// As the object is not retained by any classes, it will be deleted by the pool.
///		PoolManager::getInstance().flush();
/// }
/// \endcode
///
////////////////////////////////////////////////////////////

#endif//__SPARKY_POOL_MANAGER_HPP__