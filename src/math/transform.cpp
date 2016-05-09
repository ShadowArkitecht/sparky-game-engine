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

/*
====================
Class Includes
====================
*/
#include <sparky\math\transform.hpp>	// Class definition.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Transform::Transform(void)
		: m_position(), m_scale(Vector3f::one()), m_rotation()
	{
	}

	////////////////////////////////////////////////////////////
	Transform::Transform(const Vector3f& position, const Quaternionf& rotation)
		: m_position(position), m_scale(Vector3f::one()), m_rotation(rotation)
	{
	}

	////////////////////////////////////////////////////////////
	Transform::Transform(const Vector3f& position, const Vector3f& scale, const Quaternionf& rotation)
		: m_position(position), m_scale(scale), m_rotation(rotation)
	{
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	Vector3f Transform::getPosition(void) const
	{
		return m_position;
	}

	////////////////////////////////////////////////////////////
	void Transform::setPosition(const Vector3f& position)
	{
		m_position = position;
	}

	////////////////////////////////////////////////////////////
	Vector3f Transform::getScale(void) const
	{
		return m_scale;
	}

	////////////////////////////////////////////////////////////
	void Transform::setScale(const Vector3f& scale)
	{
		m_scale = scale;
	}

	////////////////////////////////////////////////////////////
	Quaternionf Transform::getRotation(void) const
	{
		return m_rotation;
	}

	////////////////////////////////////////////////////////////
	void Transform::setRotation(const Quaternionf& rotation)
	{
		m_rotation = rotation;
	}

	////////////////////////////////////////////////////////////
	Matrix4f Transform::getTransformation(void) const
	{
		Matrix4f s = Matrix4f::scale(m_scale);
		Matrix4f r = m_rotation.toMatrix();
		Matrix4f t = Matrix4f::translation(m_position);

		return (s * r * t);
	}

	/*
	====================
	Methods
	====================
	*/
	void Transform::translate(const Vector3f& translation)
	{
		m_position += translation;
	}

	////////////////////////////////////////////////////////////
	void Transform::rotate(const Quaternionf& rotation)
	{
		m_rotation *= rotation;
	}

	////////////////////////////////////////////////////////////
	Vector3f Transform::right(void) const
	{
		return m_rotation.right();
	}

	////////////////////////////////////////////////////////////
	Vector3f Transform::up(void) const
	{
		return m_rotation.up();
	}

	////////////////////////////////////////////////////////////
	Vector3f Transform::forward(void) const
	{
		return m_rotation.forward();
	}

}//namespace sparky