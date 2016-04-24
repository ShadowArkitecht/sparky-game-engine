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

#ifndef __SPARKY_QUATERNION_HPP__
#define __SPARKY_QUATERNION_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\math\matrix4.hpp>		// Quaternions need to be converted into Matrices for OpenGL shaders.
#include <sparky\math\mathutils.hpp>	// Conversion of radians to degrees.

namespace sparky
{
	template <typename T>
	class Quaternion final
	{
	public:
		/*
		====================
		Member Variables
		====================
		*/
		T x; // x (right) component.
		T y; // y (up) component.
		T z; // z (forward) component 
		T w; // w (rotation) component.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Quaternion object.
		///
		/// Constructs a Quaternion object set to the identity [ 0, 0, 0, 1 ].
		/// 
		////////////////////////////////////////////////////////////
		explicit Quaternion(void);

		////////////////////////////////////////////////////////////
		/// \breif Constructs a Quaternion object with x, y, z and w values.
		/// 
		/// \param x	The x value.
		/// \param y	The y value.
		/// \param z	The z value.
		/// \param w	The w value.
		///
		////////////////////////////////////////////////////////////
		explicit Quaternion(const T x, const T y, const T z, const T w);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Quaternion object from the member of another.
		///
		/// \param quaternion	The Quaternion object the parameters are read from.
		///
		////////////////////////////////////////////////////////////
		template <typename U> explicit Quaternion(const Quaternion<U>& quaternion);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Quaternion object from a Matrix4.
		///
		/// This rotations of the Matrix4 are used to construct the 
		/// rotation of the Quaternion object.
		/// 
		/// \param matrix	The matrix referenced for Quaternion rotational construction.
		///
		////////////////////////////////////////////////////////////
		explicit Quaternion(const Matrix4<T>& matrix);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Quaternion object.
		////////////////////////////////////////////////////////////
		~Quaternion(void) = default;

		/*
		====================
		Operators
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator for two Quaternion objects.
		///
		/// When a Quaternion is multiplied by another, it applies the
		/// rotation of one onto the other. The method will return the
		/// result as a new Quaternion object.
		///
		/// \param quaternion	The quaternion to be multiplied by.
		///
		/// \retval Quaternion	Member-wise multiplication of the two quaternions.
		///
		////////////////////////////////////////////////////////////
		Quaternion operator*(const Quaternion& quaternion) const;

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator for a Quaternion and a Vector.
		///
		/// When a Quaternion is multiplied by a vector, it applies the
		/// position of the Vector to the quaternion. The method will return
		/// the result as a new Quaternion object.
		///
		/// \param vector		The Vector to be multiplied by.
		///
		/// \retval Quaternion	Member-wise multiplication of a Quaternion and
		///						Vector.
		///
		////////////////////////////////////////////////////////////
		Quaternion operator*(const Vector3<T>& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Division operator for two Quaternion objects.
		///
		/// When a Quaternion is divided by another, it applies a member
		/// wise division of all member variables. The result is returned
		/// as a new Quaternion object.
		///
		/// \param quaternion	The Quaternion to be divided by.
		///
		/// \retval Quaternion	Member-wise division of a Quaternion.
		///
		////////////////////////////////////////////////////////////
		Quaternion operator/(const Quaternion& quaternion) const;

		////////////////////////////////////////////////////////////
		/// \brief Division operator for a Quaternion and a value
		///
		/// When a Quaternion is divided by a value, it applies a member
		/// wise division of all member variables. The result is returned
		/// as a new Quaternion object.
		///
		/// \param quaternion	The Quaternion to be divided by.
		///
		/// \retval Quaternion	Member-wise division of a Quaternion by a value.
		///
		////////////////////////////////////////////////////////////
		Quaternion operator/(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator for two Quaternion objects.
		///
		/// When a Quaternion is multiplied by another, it applies the
		/// rotation of one onto the other. The method will return the
		/// reference of this object after mulitplication
		///
		/// \param quaternion	The quaternion to be multiplied by.
		///
		/// \retval Quaternion	A reference to this object.
		///
		////////////////////////////////////////////////////////////
		const Quaternion& operator*=(const Quaternion& quaternion);

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator for a Quaternion and a Vector
		///
		/// When a Quaternion is multiplied by a vector, it applies the
		/// position of the Vector to the quaternion. The method will 
		/// return a reference to this object.
		///
		/// \param vector		The Vector to be multiplied by.
		///
		/// \retval Quaternion	A reference to this object.
		///
		////////////////////////////////////////////////////////////
		const Quaternion& operator*=(const Vector3<T>& vector);

		////////////////////////////////////////////////////////////
		/// \brief Division operator for two Quaternion objects.
		///
		/// When a Quaternion is divided by another, it applies a member
		/// wise division of all member variables. This method will return
		/// a reference to this object.
		///
		/// \param quaternion	The Quaternion to be divided by.
		///
		/// \retval Quaternion	A reference to this object.
		///
		////////////////////////////////////////////////////////////
		const Quaternion& operator/=(const Quaternion& quaternion);

		////////////////////////////////////////////////////////////
		/// \brief Division operator for a Quaternion and a value
		///
		/// When a Quaternion is divided by a value, it applies a member
		/// wise division of all member variables. This method will return
		/// a reference to this object.
		///
		/// \param quaternion	The Quaternion to be divided by.
		///
		/// \retval Quaternion	A reference to this object.
		///
		////////////////////////////////////////////////////////////
		const Quaternion& operator/=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Equality operator between two Quaternion objects.
		///
		/// If the members of each Quaternion are the same, then the
		/// Quaternions are equal to one another.
		/// 
		/// \param quaternion	The quaternion to be compared.
		///
		/// \retval bool		True if the quaternions are equal.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Quaternion& quaternion);

		////////////////////////////////////////////////////////////
		/// \brief Non-equality operator between two Quaternion objects.
		///
		/// If the members of each Quaternion are not the same, then the
		/// Quaternions are not equal to one another.
		/// 
		/// \param quaternion	The quaternion to be compared.
		///
		/// \retval bool		True if the quaternions are not equal.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Quaternion& quaternion);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Conjugate calculates the current inverse of the quaternion.
		/// 
		/// \retval Quaternion	The quaternion conjugate.
		///
		////////////////////////////////////////////////////////////
		Quaternion conjugate(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Converts the Quaternion object to a Matrix4.
		///
		/// Converts the current Quaternion object back into a Matrix4. 
		/// Used primarily for communication between quaternion rotations, 
		/// and OpenGL shaders.
		/// 
		/// \retval Matrix4		A converted Quaternion matrix.
		///
		////////////////////////////////////////////////////////////
		Matrix4<T> toMatrix(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the squared magnitude/length of the quaternion. 
		/// 
		/// \retval T	The Quaternion magnitude squared.
		///
		////////////////////////////////////////////////////////////
		T magnitudeSqr(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the magnitude/length of the quaternion. 
		/// 
		/// \retval	T	The Quaternion magnitude.
		///
		////////////////////////////////////////////////////////////
		T magnitude(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the unit length of the Quaternion object.
		/// 
		/// \retval	Quaternion	The normalised Quaternion object.
		///
		////////////////////////////////////////////////////////////
		Quaternion normalised(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the dot product between two Quaternion objects.
		///
		/// The dot product is the value equal to the magnitudes/length of the
		/// two quaternion multiplied together and then multiplied by the 
		/// cosine of the angle between them.
		/// 
		/// \param u	The first quaternion.
		/// \param v	The second quaternion.
		///
		/// \retval T	The cosine angle between two Quaternions.
		///
		////////////////////////////////////////////////////////////
		static T dot(const Quaternion& u, const Quaternion& v);

		////////////////////////////////////////////////////////////
		/// \brief Calculates the angle between two Quaternions.
		///
		/// This will calculate the angle between two different quaternions. 
		/// The angle will be returned in degrees.
		/// 
		/// \param from		The quaternion where the angle measurement will begin.
		/// \param to		The quaternion where the angle measurement will end.
		///
		/// \retval T		The angle between the Quaternions in degrees.
		///
		////////////////////////////////////////////////////////////
		static T angle(const Quaternion& from, const Quaternion& to);

		////////////////////////////////////////////////////////////
		/// \brief Applies angle axis rotation to Quaternion object.
		///
		/// Rotates the quaternion around the given axis by the designated 
		/// angle. The angle must be given in degrees.
		/// 
		/// \param axis		The axis of rotation.
		/// \param angle	The angle to rotate the quaternion by.
		/// 
		/// \retval Quaternion	The rotated Quaternion object.
		///
		////////////////////////////////////////////////////////////
		static Quaternion angleAxis(const Vector3<T>& axis, const T angle);

		////////////////////////////////////////////////////////////
		/// Rotates the quaternion to look towards the given target Vector.
		/// 
		/// \param target		The target to look at.
		///
		/// \retval Quaternion	The Quaternion rotated towards the target Vector.
		///
		////////////////////////////////////////////////////////////
		static Quaternion lookRotation(const Vector3<T>& target);

		/*
		====================
		Properties
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a Quaternion identity.
		///
		/// Constructs an identity Quaternion and returns this identity object. 
		/// This is a Quaternion that effectively does nothing when multiplied. 
		/// It has a 1 in the w component and 0s in all other elements. [ 0 0 0 1 ]
		/// 
		/// \retval A Quaternion identity.
		///
		////////////////////////////////////////////////////////////
		static Quaternion identity(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Quaternion with all elements set to 0.
		///		   [ 0 0 0 0 ]
		///
		/// \retval	Quaternion	A Quaternion object with all members equalling 0.
		///
		////////////////////////////////////////////////////////////
		static Quaternion zero(void);

		////////////////////////////////////////////////////////////
		/// \brief Calculates the local right axis of the Quaternion.
		/// 
		/// \retval Vector3		The local Quaternion right axis.
		///
		////////////////////////////////////////////////////////////
		Vector3<T> right(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the local up axis of the Quaternion.
		/// 
		/// \retval Vector3		The local Quaternion up axis.
		///
		////////////////////////////////////////////////////////////
		Vector3<T> up(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the local forward axis of the Quaternion.
		/// 
		/// \retval Vector3		The local Quaternion forward axis.
		///
		////////////////////////////////////////////////////////////
		Vector3<T> forward(void) const;

	};

#include <sparky\math\quaternion.inl>

	typedef Quaternion<int> Quaternioni;
	typedef Quaternion<float> Quaternionf;


}//namespace sparky

#endif//__SPARKY_QUATERNION_HPP__