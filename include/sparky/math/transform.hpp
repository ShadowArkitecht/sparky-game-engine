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

#ifndef __SPARKY_TRANSFORM_HPP__
#define __SPARKY_TRANSFORM_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\math\quaternion.hpp>	// Transforms rotation orientation.

namespace sparky
{
	class Transform final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Vector3f    m_position;
		Vector3f    m_scale;
		Quaternionf m_rotation;

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit Transform(void);
		~Transform(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		Vector3f getPosition(void) const;
		void setPosition(const Vector3f& position);

		Vector3f getScale(void) const;
		void setScale(const Vector3f& scale);

		Quaternionf getRotation(void) const;
		void setRotation(const Quaternionf& rotation);

		Matrix4f getTransformation(void) const;
	};

}//namespace sparky

#endif//__SPARKY_TRANSFORM_HPP__