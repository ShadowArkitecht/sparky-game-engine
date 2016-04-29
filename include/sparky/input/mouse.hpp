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

#ifndef __SPARKY_MOUSE_HPP__
#define __SPARKY_MOUSE_HPP__

#include <array>
/*
====================
Class Includes
====================
*/
#include <sparky\input\ievent.hpp>	// IEventComponent is an event driven class.
#include <sparky\math\vector2.hpp>	// Stores position and delta of mouse.

namespace sparky
{
	enum class eMouseButton
	{
		LEFT,
		RIGHT,
		MAX
	};

	class Mouse final : public IEventComponent
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		std::array<bool, static_cast<int>(eMouseButton::MAX)> m_currentButtons;	// Buttona currently pressed.
		std::array<bool, static_cast<int>(eMouseButton::MAX)> m_downButtons;	// Buttons being held down.
		std::array<bool, static_cast<int>(eMouseButton::MAX)> m_upButtons;		// Buttons that have been released.

		Vector2i m_position;													// The mouse cursor position.
		Vector2i m_delta;														// The delta movement of the cursor.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor of the Mouse object.
		///
		/// All of the member variables are set to false to default
		/// values.
		///
		////////////////////////////////////////////////////////////
		Mouse(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the Mouse object.
		////////////////////////////////////////////////////////////
		~Mouse(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the current position of the Mouse object.
		///
		/// \retval Vector2i	The position of the Mouse.
		///
		////////////////////////////////////////////////////////////
		const Vector2i& getPosition(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the delta movement of the Mouse object.
		///
		/// The delta is the amount the mouse has moved between the current
		/// frame. and previous frame.
		///
		/// \retval Vector2i	The delta of the Mouse object.
		///
		////////////////////////////////////////////////////////////
		const Vector2i& getDelta(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the state of the mouse button.
		///
		/// Get button will return true continuously whilst the button
		/// is held down.
		///
		/// \retval bool	The state of the specified button.
		///
		////////////////////////////////////////////////////////////
		bool getButton(const eMouseButton button);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the state of the mouse button.
		///
		/// Get button down will return true once at the beginning pf the
		/// frame when the button is pressed.
		///
		/// \retval bool	The state of the specified button.
		///
		////////////////////////////////////////////////////////////
		bool getButtonDown(const eMouseButton button);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the state of the mouse button.
		///
		/// Get button will return true only when the specified button
		/// has been released.
		///
		/// \retval bool	The state of the specified button.
		///
		////////////////////////////////////////////////////////////
		bool getButtonUp(const eMouseButton button);

		////////////////////////////////////////////////////////////
		/// \brief Updates the events of the Mouse object.
		///
		/// \param e	The SDL_Event being passed in from the Event Manager.
		///
		////////////////////////////////////////////////////////////
		void update(const SDL_Event& e) override;
	};

}//namespace sparky

#endif//__SPARKY_MOUSE_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Mouse
/// \ingroup input
///
/// sparky::Mouse is an event component class that is responsible
/// for reading mouse buttons and mouse states from the mouse. sparky::Mouse
/// has different methods for different interactions with the mouse,
/// such as checking when a button has first been pressed, held down, or
/// released.
///
/// As sparky::Mouse is an event component the events of sparky::Mouse
/// are polled in the event manager singleton, therefore the user does
/// need to worry about polling the system themselves. Below is a code 
/// example.
///
/// \code
/// // Create a mouse object.
/// sparky::Mouse* pMouse = new sparky::Mouse();
///
/// // if the left mouse button has been released, print a message.
/// if (pMouse->getButtonUp(eMouseButton::LEFT))
/// {
///		std::cout << "Left button released!" << std::endl;
/// }
///
////////////////////////////////////////////////////////////