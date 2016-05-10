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

#ifndef __SPARKY_TIME_HPP__
#define __SPARKY_TIME_HPP__

namespace sparky
{
	class Time final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		static long   m_sCurrentTime;	///< The current time of the frame, stored at the start of each frame.
		static double m_sDeltaTime;		///< The recorded time between the current frame, and the previous frame.
		static long   m_sLastTime;		///< The time the last frame took to render, update and retrieve input.

	public:
		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the delta-time of the current frame.
		///
		/// The delta-time is calculated at the end of the current frame.
		/// It is the time that the frame took to render, update and process
		/// the input of the current frame.
		///
		/// \retval float	The current delta-time of the frame. 
		///
		////////////////////////////////////////////////////////////
		static float getDeltaTime(void);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Starts the timer to calculate the beginning time of the current
		///        frame.
		////////////////////////////////////////////////////////////
		static void start(void);

		////////////////////////////////////////////////////////////
		/// \brief Stops the timer and calculates the time that it took to render and update this frame, 
		///		   this value is stored in delta-time for use by other objects and instances.
		////////////////////////////////////////////////////////////
		static void stop(void);
	};

}//namespace sparky

#endif//__SPARKY_TIME_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Time
/// \ingroup core
///
/// sparky::Time is responsible for tracking the delta-time of each frame.
/// At the beginning of each frame, the timer is start and at the end of
/// the frame, the timer is stopped and delta-time is calculated accordingly.
/// Below is a code example.
///
/// Usage Example:
/// \code
/// // Start the timer.
/// Time::start();
///
/// // Create a Transform object.
/// sparky::Transform transform;
///
/// // Apply a rotation to the transform by utilising delta-time for smooth rotation.
/// sparky::Quaternionf rotation = sparky::Quaternionf::angleAxis(sparky::Vector3f::up(), 5.0f * sparky::Time::getDeltaTime());
///
/// // Apply the rotation to the transform object.
/// transform.rotate(rotation);
///
/// // Stop the timer.
/// Time::stop();
/// \endcode
///
////////////////////////////////////////////////////////////