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

#ifndef __SPARKY_INPUT_HPP__
#define __SPARKY_INPUT_HPP__

/*
====================
CPP Includes
====================
*/
#include <array>					// C++ Array containers for key states.
/*
====================
Class Includes
====================
*/
#include <sparky\input\ievent.hpp>	// Input is a type of event class.

namespace sparky
{
	class Input final : public IEventComponent
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::array<bool, 512> m_currentKeys;	// The keys currently being held.
		std::array<bool, 512> m_downKeys;		// The keys currently pressed.
		std::array<bool, 512> m_upKeys;			// The keys that are about to be released.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default input constructor. Sets all the keys to false.
		////////////////////////////////////////////////////////////
		explicit Input(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor that de-allocates the Input.
		////////////////////////////////////////////////////////////
		~Input(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the state of the specified key.
		///
		/// Get Key will return true whilst the specified key is held
		/// down.
		///
		/// \retval bool	True if the key is being held down.
		///
		////////////////////////////////////////////////////////////
		bool getKey(const SDL_Keycode& key) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the state of the specified key.
		///
		/// Get Key down will return once when the key is held down at
		/// the beginning of the frame, and will return true whilst the
		/// key is still held down.
		///
		/// \retval bool	True if the key has been pressed.
		///
		////////////////////////////////////////////////////////////
		bool getKeyDown(const SDL_Keycode& key) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the state of the specified key.
		///
		/// Get key up will return once a key currently being held down
		/// is released.
		///
		/// \retval bool	True if the key has been released.
		///
		////////////////////////////////////////////////////////////
		bool getKeyUp(const SDL_Keycode& key) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Updates the states and events of the Keyboard input.
		////////////////////////////////////////////////////////////
		void update(const SDL_Event& e) override;
	};

}//namespace sparky

#endif//__SPARKY_INPUT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Input
/// \ingroup input
///
/// sparky::Input is an event component class that is responsible
/// for reading input and states from the keyboard. sparky::Input
/// has different methods for different interactions with the keyboard,
/// such as checking when a key has first been pressed, held down, or
/// released.
///
/// As sparky::Input is an event component the events of sparky::Input
/// are polled in the event manager singleton, therefore the user does
/// need to worry about polling the system themselves. Below is a code 
/// example.
///
/// \code
/// // Create a new sparky::Input object for use.
/// sparky::Input* pInput = new sparky::Input();
///
/// // check if a has been released and print a message if it has.
/// // should be inside the game loop.
/// if (pInput->getKeyUp(SDLK_a))
/// {
///		std::cout << "A was released!" << std::endl;
/// }
///
////////////////////////////////////////////////////////////