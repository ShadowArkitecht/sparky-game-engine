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

#ifndef __SPARKY_MATH_UTILS_HPP__
#define __SPARKY_MATH_UTILS_HPP__

namespace sparky
{
	template <typename T>
	class MathUtils final
	{
	public:
		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Converts a radian value into degrees.
		///
		/// \param radians	The radian value to convert.
		///
		/// \retval T		The radian value in degrees.
		///
		////////////////////////////////////////////////////////////
		static T toDegrees(const T radians)
		{
			const T PI = static_cast<T>(3.14f);
			return radians * (static_cast<T>(180.0f) / PI);
		}

		////////////////////////////////////////////////////////////
		/// \brief Converts a degrees value into radians.
		///
		/// \param degrees	The degrees value to convert.
		///
		/// \retval T		The degrees value in radians.
		///
		////////////////////////////////////////////////////////////
		static T toRadians(const T degrees)
		{
			const float PI = static_cast<T>(3.14f);
			return degrees * (PI / static_cast<T>(180.0f));
		}
	};

}//namespace sparky

#endif//__SPARKY_MATH_UTILS_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::MathUtils
/// \ingroup math
///
/// sparky::MathUtils is a collection of useful Math methods
/// that are commonly used throughout the mathematics section
/// of the engine. It is used for conversion between degrees and
/// radian values.
///
////////////////////////////////////////////////////////////