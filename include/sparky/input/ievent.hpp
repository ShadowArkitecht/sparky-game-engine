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

#ifndef __SPARKY_IEVENT_COMPONENT_HPP__
#define __SPARKY_IEVENT_COMPONENT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>	// IEvent will be a dynamically allocated object.
/*
====================
Additional Includes
====================
*/
#include <SDL2\SDL.h>			// SDL Event handling.

namespace sparky
{
	class IEventComponent : public Ref
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the IEventComponent object.
		///
		/// The constructor of this object will call the parent Ref
		/// constructor and add this object to the event manager for
		/// polling.
		///
		////////////////////////////////////////////////////////////
		IEventComponent(void);

		////////////////////////////////////////////////////////////
		/// \brief Destructor of the Event component object.
		///
		/// The destructor will remove this event from event manager
		/// polling system.
		///
		////////////////////////////////////////////////////////////
		virtual ~IEventComponent(void);
		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Abstract update method that needs to be overwritten
		///        by children for additional behaviour.
		///
		/// \param e	The SDL_Event to polling events from.
		///
		////////////////////////////////////////////////////////////
		virtual void update(const SDL_Event& e) = 0;
	};

}//namespace sparky

#endif//__SPARKY_IEVENT_COMPONENT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::IEventComponent
/// \ingroup input	
///
/// sparky::IEventComponent is an abstract class that all event
/// handling and input classes inherit from. It contains abstract
/// methods which will be called within the event manager singleton
/// class. Additional use and code examples are provided in 
/// sparky::Input and sparky::Mouse.
///
////////////////////////////////////////////////////////////