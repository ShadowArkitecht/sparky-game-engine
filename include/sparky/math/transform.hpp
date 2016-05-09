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
		Vector3f    m_position;	///< The translation of the object.
		Vector3f    m_scale;	///< Scale of the object.
		Quaternionf m_rotation;	///< Objects current rotation.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Transform object.
		///
		/// The default construction of the Transform will set the position,
		/// rotation and scale to default values [ 0, 0, 0 ], [ 1, 1, 1], [ 0, 0, 0, 1 ].
		///
		////////////////////////////////////////////////////////////
		explicit Transform(void);
		
		////////////////////////////////////////////////////////////
		/// \brief Construction of the Transform object with a set position and rotation.
		///
		/// This constructor will create a Transform object with an implicitly
		/// defined position and rotation. The scale is set to [ 1, 1, 1 ].
		///
		/// \param position		The translation of the Transform object.
		/// \param rotation		The rotation of the Transform object.
		///
		////////////////////////////////////////////////////////////
		explicit Transform(const Vector3f& position, const Quaternionf& rotation);

		////////////////////////////////////////////////////////////
		/// \brief Construction of the Transform object with a set position, rotation and scale.
		///
		/// This constructor will create a Transform object with an implicitly
		/// defined position, scale and rotation.
		///
		/// \param position		The translation of the Transform object.
		/// \param scale		The scale of the Transform object.
		/// \param rotation		The rotation of the Transform object.
		///
		////////////////////////////////////////////////////////////
		explicit Transform(const Vector3f& position, const Vector3f& scale, const Quaternionf& rotation);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Transform object.
		////////////////////////////////////////////////////////////
		~Transform(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the current translation of the Transform.
		///
		/// The position refers to the objects position within the 3D
		/// environment.
		///
		/// \retval Vector3f	The current position.
		///
		////////////////////////////////////////////////////////////
		Vector3f getPosition(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the position of the current Transform to a new value.
		///
		/// The position refers to the objects position within the 3D
		/// environment.
		///
		/// \param position		The new position of the Transform object.
		///
		////////////////////////////////////////////////////////////
		void setPosition(const Vector3f& position);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the current scale of the Transform object.
		///
		/// The scale refers to how large the current object within the
		/// scene is.
		///
		/// \retval Vector3f	The current scale of the Transform.
		///
		////////////////////////////////////////////////////////////
		Vector3f getScale(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the new scale of the Transform object.
		///
		/// The scale refers to how large the current object within the
		/// scene is.
		///
		/// \param scale	The new scale of the Transform object.
		///
		////////////////////////////////////////////////////////////
		void setScale(const Vector3f& scale);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the rotation of the current Transform object.
		///
		/// The rotation refers to the current orientation of the object.
		/// As the application uses Quaternions, there is no gimbal lock.
		///
		/// \retval Quaternionf		The current rotation of the Transform object.
		///
		////////////////////////////////////////////////////////////
		Quaternionf getRotation(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets a new rotation of the Transform object.
		///
		/// The rotation refers to the current orientation of the object.
		/// As the application uses Quaternions, there is no gimbal lock.
		///
		/// \param rotation		The new rotation of the Transform.
		///
		////////////////////////////////////////////////////////////
		void setRotation(const Quaternionf& rotation);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the transformation of the Transform object.
		///
		/// The transformation refers to the transformation matrix of the 
		/// current Transform object. The transformation matrix is the combined
		/// matrix of the translation, rotation and scale.
		///
		/// \retval Matrix4f	The transformation matrix of the Transform object.
		///
		////////////////////////////////////////////////////////////
		Matrix4f getTransformation(void) const;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Translates the position of the Transform by the given amount.
		///
		/// The translation will translate the current position by the specified
		/// amount, this method is just a convenience method for calculating
		/// p = p + t.
		///
		/// \param translation	The amount to move the current position by.
		///
		////////////////////////////////////////////////////////////
		void translate(const Vector3f& translation);

		////////////////////////////////////////////////////////////
		/// \brief Rotates the current rotation of the Transform by the specified amount.
		///
		/// The rotation will rotate the current rotation by the specified
		/// amount, this method is short hand for r = r * t.
		///
		/// \param rotation	The amount to rotate the current rotation by.
		///
		////////////////////////////////////////////////////////////
		void rotate(const Quaternionf& rotation);

		/*
		====================
		Properties
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the local right of the Transform object.
		///
		/// \retval Vector3f	The current right axis of the Transform.
		///
		////////////////////////////////////////////////////////////
		Vector3f right(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the local up of the Transform object.
		///
		/// \retval Vector3f	The current up axis of the Transform.
		///
		////////////////////////////////////////////////////////////
		Vector3f up(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the local forward of the Transform object.
		///
		/// \retval Vector3f	The current forward axis of the Transform.
		///
		////////////////////////////////////////////////////////////
		Vector3f forward(void) const;
	};

}//namespace sparky

#endif//__SPARKY_TRANSFORM_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Transform
/// \ingroup math
///
/// sparky::Transform is the culmination class for all of the
/// mathematic functionality within the Sparky Engine. It is
/// utilised with any object that needs a position, rotation and
/// scale within 3D space.
///
/// The Transform class is commonly used with the Camera and Chunk
/// classes. Below is a code example of using the Transform class.
///
/// Usage example:
/// \code
/// // Create the position, rotation and scale of the object.
/// sparky::Vector3f position(0.0f, 0.0f, 5.0f);
/// sparky::Vector3f scale(2.0f, 2.0f, 2.0f);
/// sparky::Quaternionf rotation(0.0f, 0.0f, 0.0f, 1.0f);
///
/// // Create the Transform object with this information.
/// sparky::Transform transform(position, scale, rotation);
///
/// // Create rotation to rotate the transform by.
/// sparky::Quaternionf axis = sparky::Quaternionf::angleAxis(sparky::Vector3f(0.0f, 1.0f, 0.0f), 5.0f * sparky::Time::getDeltaTime());
///
/// // Apply the rotation.
/// transform.rotate(axis);
/// \endcode
///
////////////////////////////////////////////////////////////