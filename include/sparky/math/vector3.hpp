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

#ifndef __SPARKY_VECTOR3_HPP__
#define __SPARKY_VECTOR3_HPP__

/*
====================
CPP Includes
====================
*/
#include <cmath>		// Needed for square root and trigonometry.
#include <algorithm>	// Finding minimum and maximum values.

namespace sparky
{
	template <typename T>
	class Vector3
	{
	public:
		/*
		====================
		Member Variables
		====================
		*/		   
		T x;	///< The x (right) value.
		T y;	///< The y (up) value.
		T z;	///< The z (forward) value.

	public:
		/*
		====================
		Constructors
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default contruction of Vector3 object. [ 0, 0, 0 ].
		////////////////////////////////////////////////////////////
		explicit Vector3(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Vector3 object with defined x, y and z
		///		   values.
		///
		/// \param x	The x value of the Vector object.
		///	\param y	The y value of the Vector object.
		///	\param z	The z value of the Vector object.
		///
		////////////////////////////////////////////////////////////
		explicit Vector3(const T x, const T y, const T z);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Vector3 object from the members of a
		///		   different Vector3.
		///
		/// \param vector	The different Vector type.
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector3(const Vector3<U>& vector);

		////////////////////////////////////////////////////////////
		/// \brief Default Vector destruction.
		////////////////////////////////////////////////////////////
		~Vector3(void) = default;

		/*
		====================
		Operators
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Addition operator between two Vectors.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and return the result as a new Vector3 object.
		///
		/// \param vector	A vector to add.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator+(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Addition operator between a Vector and a value.
		///
		/// This operator performs a member-wise addition of a Vector
		/// and a value and returns the result as a new Vector3 object.
		///
		/// \param value	The value to add.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator+(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between two Vectors.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and return the result as a new Vector3 object.
		///
		/// \param vector	A vector to subtract.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator-(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between a Vector and a value.
		///
		/// This operator performs a member-wise subtraction of a Vector
		/// and a value and returns the result as a new Vector3 object.
		///
		/// \param value	The value to subtract.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator-(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between two Vectors.
		///
		/// This operator performs a member-wise multiplication of two 
		/// vectors and return the result as a new Vector3 object.
		///
		/// \param vector	A vector to multiply.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator*(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between a Vector and a value.
		///
		/// This operator performs a member-wise multiplication of a Vector
		/// and a value and returns the result as a new Vector3 object.
		///
		/// \param value	The value to multiply.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator*(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Division operator between two Vectors.
		///
		/// This operator performs a member-wise division of two 
		/// vectors and return the result as a new Vector3 object.
		///
		/// \param vector	A vector to divide.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator/(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Division operator between a Vector and a value.
		///
		/// This operator performs a member-wise division of a Vector
		/// and a value and returns the result as a new Vector3 object.
		///
		/// \param value	The value to divide.
		///
		/// \retval Vector3	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator/(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Addition operator between two Vectors.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// \param vector	A vector to add.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator+=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// \brief Addition operator between a Vector and value.
		///
		/// This operator performs a member-wise addition of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// \param value	The value to add.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator+=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between two Vectors.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// \param vector	A vector to subtract.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator-=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between a Vector and value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// \param value	The value to subtract.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator-=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between two Vectors.
		///
		/// This operator performs a member-wise multiplication of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// \param vector	A vector to multiply.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator*=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between a Vector and value.
		///
		/// This operator performs a member-wise multiplication of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// \param value	The value to multiply.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator*=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Division operator between two Vectors.
		///
		/// This operator performs a member-wise division of two vectors
		/// and applies the result to the current Vector3 object.
		///
		/// \param vector	A vector to divide.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator/=(const Vector3& vector);

		////////////////////////////////////////////////////////////
		/// \brief Division operator between a Vector and value.
		///
		/// This operator performs a member-wise division of a vector
		/// and value and applies the result to the current Vector3 object.
		///
		/// \param value	The value to divide.
		///
		/// \retval Vector3	A reference to the current Vector3 object.
		///
		////////////////////////////////////////////////////////////
		const Vector3& operator/=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are the same, the Vector object are equal.
		///
		/// \param vector	The Vector object to compare against.
		///
		/// \retval bool	True if the Vector objects are the same.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Non-Equality operation between two vectors.
		///
		/// The operation will execute member wise comparisons. If the
		/// members are not the same, the Vector object are not equal.
		///
		/// \param vector	The Vector object to compare against.
		///
		/// \retval bool	True if the Vector objects are not the same.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Vector3& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Unary Operation on a Vector object.
		///
		/// This will invert the x and y components from positive to negative
		/// values, and vice-versa.
		///
		/// \retval Vector3		An inverted Vector object.
		///
		////////////////////////////////////////////////////////////
		Vector3 operator-(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Overload the output stream operator to print a Vector3
		///        to the console window.
		///
		/// This method can be used for debugging processes to print a
		/// vector to the console window. The matrix will be printed in the
		/// following format:
		///
		/// [ x, y, z ]
		///
		/// \param os		The output stream to stream into.
		/// \param vector	The vector to print to the console window.
		///
		/// \retval ostream	The stream of the object.
		///
		////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Vector3& vector)
		{
			return os << "[ " << vector.x << ", " << vector.y << ", " << vector.z << " ]";
		}

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Calculates the squared length of the Vector object.
		///
		/// \retval T	The squared length of the Vector.
		///
		////////////////////////////////////////////////////////////
		T magnitudeSqr(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the length of the Vector object. 
		///
		/// \retval T	The length of the Vector.
		///
		////////////////////////////////////////////////////////////
		T magnitude(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculates the unit length of the Vector object.
		///
		/// \retval Vector3		The normalised Vector object.
		///
		////////////////////////////////////////////////////////////
		Vector3 normalised(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Calculate the cosine angle between two Vector objects.
		///
		/// The dot product is the value equal to the magnitudes/length of 
		/// the two vectors multiplied together and then multiplied by the 
		/// cosine of the angle between them.
		///
		/// \param u	The first vector.
		/// \param v	The second vector.
		///
		/// \retval T	The cosine angle between two Vectors/
		///
		////////////////////////////////////////////////////////////
		static T dot(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// \brief Calculate the cross product of two Vector object.
		///
		/// The cross product is a mathematical function which uses two
		/// vectors and results in a third vector which is perpendicular 
		/// to the Vector objects.
		/// 
		/// \param u	The first vector.
		/// \param v	The second vector.
		///
		/// \retval	Vector3		The Vector perpendicular to the two Vector objects.
		///
		////////////////////////////////////////////////////////////
		static Vector3 cross(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// \brief Gets the (degrees) angle between two Vector objects.
		///
		/// This will calculate the angle between two different vectors. The angle 
		/// will be returned in degrees.
		/// 
		/// \param from		The vector where the angle measurement will begin.
		/// \param to		The vector where the angle measurement will end.
		///
		/// \retval T		The angle between the Vectors in degrees.
		///
		////////////////////////////////////////////////////////////
		static T angle(const Vector3& from, const Vector3& to);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the squared euclidean distance between two different Vectors.
		/// 
		/// \param from		The starting vector.
		/// \param to		The vector distance to measure.
		///
		/// \retval T		The squared euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distanceSqr(const Vector3& from, const Vector3& to);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the euclidean distance between two different Vectors.
		/// 
		/// \param from		The starting vector.
		/// \param to		The vector distance to measure.
		///
		/// \retval T		The euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distance(const Vector3& from, const Vector3& to);

		////////////////////////////////////////////////////////////
		/// \brief Gets the minimum values of two Vector objects.
		///
		/// This will get the lowest member values of the two Vector
		/// objects and create a new Vector constructed of the low
		/// values.
		///
		/// \param u		The first vector.
		/// \param v		The second vector.
		///
		/// \retval Vector3	The minimum x, y and z values of the two Vectors.
		///
		////////////////////////////////////////////////////////////
		static Vector3 minimum(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// \brief Gets the maximum values of two Vector objects.
		///
		/// This will get the highest member values of the two Vector
		/// objects and create a new Vector constructed of the high
		/// values.
		///
		/// \param u		The first vector.
		/// \param v		The second vector.
		///
		/// \retval Vector3	The maximum x, y and z values of the two Vectors.
		///
		////////////////////////////////////////////////////////////
		static Vector3 maximum(const Vector3& u, const Vector3& v);

		////////////////////////////////////////////////////////////
		/// \brief Moves a Vector towards the target.
		///
		/// The method will return a Vector moving from the current
		/// Vector towards the target by the specified speed.
		///
		/// \param current	The current Vector to move from.
		/// \param target	The Vector to move towards.
		/// \param speed	The speed of movement.
		///
		/// \retval	Vector3 The moved Vector.
		///
		////////////////////////////////////////////////////////////
		static Vector3 moveTowards(const Vector3& current, const Vector3& target, const T speed);

		////////////////////////////////////////////////////////////
		/// \brief Vector linear interpolation.
		///
		/// Linearly interpolates between the current Vector and target
		/// by the specfied speed.
		/// 
		/// \param current	The vector being linearly interpolated from.
		/// \param target	The vector linearly interpolated towards.
		/// \param speed	The speed of the interpolation.
		///
		/// \retval Vector3	The interpolated Vector.
		///
		////////////////////////////////////////////////////////////
		static Vector3 lerp(const Vector3& current, const Vector3& target, const T speed);

		/*
		====================
		Properties
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 0, 0, 0 ].
		///
		/// \retval Vector3		A Vector object equal to [ 0, 0, 0 ].
		///
		////////////////////////////////////////////////////////////
		static Vector3 zero(void);

		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 1, 1, 1 ].
		///
		/// \retval Vector3		A Vector object equal to [ 1, 1, 1 ].
		///
		////////////////////////////////////////////////////////////
		static Vector3 one(void);

		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 1, 0, 0 ].
		///
		/// \retval Vector3		A Vector object equal to [ 1, 0, 0 ].
		///
		////////////////////////////////////////////////////////////
		static Vector3 right(void);

		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 0, 1, 0 ].
		///
		/// \retval Vector3		A Vector object equal to [ 0, 1, 0 ].
		///
		////////////////////////////////////////////////////////////
		static Vector3 up(void);

		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 0, 0, 1 ].
		///
		/// \retval Vector3		A Vector object equal to [ 0, 0, 1 ].
		///
		////////////////////////////////////////////////////////////
		static Vector3 forward(void);
	};

	#include <sparky\math\vector3.inl>

	/*
	====================
	Type Definitions
	====================
	*/
	typedef Vector3<unsigned int> Vector3u;
	typedef Vector3<int> Vector3i;
	typedef Vector3<float> Vector3f;

}// namspace sparky

#endif//__SPARKY_VECTOR3_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Vector3<T>
/// \ingroup math
///
/// sparky::Vector3<T> is a templated class responsible for
/// all Vector based mathematics in 3 dimensions. It is commonly
/// used throughout the engine for a variety of different tasks,
/// such as placement of objects within a scene and accessing
/// multi-dimensional arrays.
///
/// sparky::Vecto3<T> also contains the most common mathematics
/// and algorithms associated with Vectors, such as the cross 
/// product and normalisation. Below is a small code example.
///
/// Usage example:
/// \code
/// // Create two vectors to calculate the cross product.
/// sparky::Vector3f v1 = sparky::Vector3f::up();
/// sparky::Vector3f v2 = sparky::Vector3f::right();
///
/// // Calculate the cross product. ( The result will be the forward ).
/// sparky::Vector3f f = sparky::Vector3f::cross(up, right);
///
/// // Normalise it.
/// f = f.normalised();
/// \endcode
///
////////////////////////////////////////////////////////////