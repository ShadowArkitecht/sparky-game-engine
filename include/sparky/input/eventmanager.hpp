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

#ifndef __SPARKY_EVENT_MANAGER_HPP__
#define __SPARKY_EVENT_MANAGER_HPP__

/*
====================
CPP Includes
====================
*/
#include <vector>						// The container for the events to be polled.
/*
====================
Class Includes
====================
*/
#include <sparky\utils\singleton.hpp>	// EventManager is a singleton object.
/*
====================
Additional Includes
====================
*/
#include <SDL2\SDL.h>					// Handling the events of the application.

namespace sparky
{
	/*
	====================
	Forward Declarations
	====================
	*/
	class IEventComponent;

	class EventManager : public Singleton<EventManager>
	{
		friend class Singleton<EventManager>;

	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::vector<IEventComponent*> m_events;		// The events being polled by the Manager.

	private:
		/*
		====================
		Ctor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Private default constructor. Sets member to default values.
		////////////////////////////////////////////////////////////
		EventManager(void);

	public:
		/*
		====================
		Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Destructor of the EventManager.
		///
		/// The destructor releases all of the events being polled by
		/// the EventManager object and clears the containers.
		///
		////////////////////////////////////////////////////////////
		~EventManager(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Adds a poll to the list for input handling.
		///
		/// \param pEvent	The event to add to the polling list.
		///
		////////////////////////////////////////////////////////////
		void addPoll(IEventComponent* pEvent);

		////////////////////////////////////////////////////////////
		/// \brief Removes a poll from the polling list.
		///
		/// \param pEvent	The event to remove from the polling list.
		///
		////////////////////////////////////////////////////////////
		void removePoll(IEventComponent* pEvent);

		////////////////////////////////////////////////////////////
		/// \brief Loops through all of the events within the list and
		///		   updates their inputs and events.
		////////////////////////////////////////////////////////////
		void poll(void);

		////////////////////////////////////////////////////////////
		/// \brief Clears all of the events within the polling system.
		////////////////////////////////////////////////////////////
		void clear(void);
	};

}//namespace sparky

#endif//__SPARKY_EVENT_MANAGER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::EventManager
/// \ingroup input
///
/// sparky::EventManager is a singleton class responsible for the
/// polling and event handling of all event-driven classes within
/// the sparky application.
///
/// sparky::EventManager never needs to be called directly by
/// the user, instead the polling will continuously run in the back
/// ground and execute all events. When an event object is created,
/// it is automatically added to sparky::EventManager for polling.
///
////////////////////////////////////////////////////////////