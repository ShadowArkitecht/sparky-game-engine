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

#ifndef __SPARKY_VECTOR4_HPP__
#define __SPARKY_VECTOR4_HPP__

namespace sparky
{
	template <typename T>
	class Vector4 final
	{
	public:
		/*
		====================
		Member Variables
		====================
		*/
		T x;
		T y;
		T z;
		T w;

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default contruction of Vector4 object. [ 0, 0, 0, 0 ].
		////////////////////////////////////////////////////////////
		explicit Vector4(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Vector4 object with defined x and y
		///		   values.
		///
		/// \param x	The x value of the Vector object.
		///	\param y	The y value of the Vector object.
		/// \param z	The z value of the Vector object.
		///	\param w	The w value of the Vector object.
		///
		////////////////////////////////////////////////////////////
		explicit Vector4(const T x, const T y, const T z, const T w);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Vector4 object from the members of a
		///		   different Vector4.
		///
		/// \param vector	The different Vector type.
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Vector4(const Vector4<U>& vector);

		////////////////////////////////////////////////////////////
		/// \brief Default Vector destruction.
		////////////////////////////////////////////////////////////
		~Vector4(void) = default;

		/*
		====================
		Operators
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Addition operator between two Vectors.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and return the result as a new Vector4 object.
		///
		/// \param vector	A vector to add.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator+(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Addition operator between a Vector and a value.
		///
		/// This operator performs a member-wise addition of a Vector
		/// and a value and returns the result as a new Vector4 object.
		///
		/// \param value	The value to add.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator+(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between two Vectors.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and return the result as a new Vector4 object.
		///
		/// \param vector	A vector to subtract.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator-(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between a Vector and a value.
		///
		/// This operator performs a member-wise subtraction of a Vector
		/// and a value and returns the result as a new Vector4 object.
		///
		/// \param value	The value to subtract.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator-(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between two Vectors.
		///
		/// This operator performs a member-wise multiplication of two 
		/// vectors and return the result as a new Vector4 object.
		///
		/// \param vector	A vector to multiply.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator*(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between a Vector and a value.
		///
		/// This operator performs a member-wise multiplication of a Vector
		/// and a value and returns the result as a new Vector4 object.
		///
		/// \param value	The value to multiply.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator*(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Division operator between two Vectors.
		///
		/// This operator performs a member-wise division of two 
		/// vectors and return the result as a new Vector4 object.
		///
		/// \param vector	A vector to divide.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator/(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Division operator between a Vector and a value.
		///
		/// This operator performs a member-wise division of a Vector
		/// and a value and returns the result as a new Vector4 object.
		///
		/// \param value	The value to divide.
		///
		/// \retval Vector4	A new Vector object made from the result.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator/(const T value) const;

		////////////////////////////////////////////////////////////
		/// \brief Addition operator between two Vectors.
		///
		/// This operator performs a member-wise addition of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// \param vector	A vector to add.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator+=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// \brief Addition operator between a Vector and value.
		///
		/// This operator performs a member-wise addition of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// \param value	The value to add.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator+=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between two Vectors.
		///
		/// This operator performs a member-wise subtraction of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// \param vector	A vector to subtract.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator-=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// \brief Subtraction operator between a Vector and value.
		///
		/// This operator performs a member-wise subtraction of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// \param value	The value to subtract.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator-=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between two Vectors.
		///
		/// This operator performs a member-wise multiplication of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// \param vector	A vector to multiply.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator*=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// \brief Multiplication operator between a Vector and value.
		///
		/// This operator performs a member-wise multiplication of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// \param value	The value to multiply.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator*=(const T value);

		////////////////////////////////////////////////////////////
		/// \brief Division operator between two Vectors.
		///
		/// This operator performs a member-wise division of two vectors
		/// and applies the result to the current Vector4 object.
		///
		/// \param vector	A vector to divide.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator/=(const Vector4& vector);

		////////////////////////////////////////////////////////////
		/// \brief Division operator between a Vector and value.
		///
		/// This operator performs a member-wise division of a vector
		/// and value and applies the result to the current Vector4 object.
		///
		/// \param value	The value to divide.
		///
		/// \retval Vector4	A reference to the current Vector4 object.
		///
		////////////////////////////////////////////////////////////
		const Vector4& operator/=(const T value);

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
		bool operator==(const Vector4& vector) const;

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
		bool operator!=(const Vector4& vector) const;

		////////////////////////////////////////////////////////////
		/// \brief Unary Operation on a Vector object.
		///
		/// This will invert the x and y components from positive to negative
		/// values, and vice-versa.
		///
		/// \retval Vector4		An inverted Vector object.
		///
		////////////////////////////////////////////////////////////
		Vector4 operator-(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Overload the output stream operator to print a Vector4
		///        to the console window.
		///
		/// This method can be used for debugging processes to print a
		/// vector to the console window. The matrix will be printed in the
		/// following format:
		///
		/// [ x, y, z, w ]
		///
		/// \param os		The output stream to stream into.
		/// \param matrix	The matrix to print to the console window.
		///
		/// \retval ostream	The stream of the object.
		///
		////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Vector4& vector)
		{
			return os << "[ " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << " ]";
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
		/// \retval Vector4		The normalised Vector object.
		///
		////////////////////////////////////////////////////////////
		Vector4 normalised(void) const;

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
		static T dot(const Vector4& u, const Vector4& v);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the squared euclidean distance between two different Vectors.
		/// 
		/// \param from		The starting vector.
		/// \param to		The vector distance to measure.
		///
		/// \retval T		The squared euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distanceSqr(const Vector4& from, const Vector4& to);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the euclidean distance between two different Vectors.
		/// 
		/// \param from		The starting vector.
		/// \param to		The vector distance to measure.
		///
		/// \retval T		The euclidean distance.
		///
		////////////////////////////////////////////////////////////
		static T distance(const Vector4& from, const Vector4& to);

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
		/// \retval Vector4	The minimum x, y and z values of the two Vectors.
		///
		////////////////////////////////////////////////////////////
		static Vector4 minimum(const Vector4& u, const Vector4& v);

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
		/// \retval Vector4	The maximum x, y and z values of the two Vectors.
		///
		////////////////////////////////////////////////////////////
		static Vector4 maximum(const Vector4& u, const Vector4& v);

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
		/// \retval	Vector4 The moved Vector.
		///
		////////////////////////////////////////////////////////////
		static Vector4 moveTowards(const Vector4& current, const Vector4& target, const T speed);

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
		/// \terval Vector4	The interpolated Vector.
		///
		////////////////////////////////////////////////////////////
		static Vector4 lerp(const Vector4& current, const Vector4& target, const T speed);

		/*
		====================
		Properties
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 0, 0, 0, 0 ].
		///
		/// \retval Vector4		A Vector object equal to [ 0, 0, 0, 0 ].
		///
		////////////////////////////////////////////////////////////
		static Vector4 zero(void);

		////////////////////////////////////////////////////////////
		/// \brief Convenience method for initialising a Vector to [ 1, 1, 1, 1 ].
		///
		/// \retval Vector4		A Vector object equal to [ 1, 1, 1, 1 ].
		///
		////////////////////////////////////////////////////////////
		static Vector4 one(void);
	};

#include <sparky\math\vector4.inl>

	typedef Vector4<int> Vector4i;
	typedef Vector4<unsigned int> Vector4u;
	typedef Vector4<float> Vector4f;

}//namespace sparky

#endif//__SPARKY_VECTOR4_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Vector4<T>
/// \ingroup math
///
/// sparky::Vector4<T> is a templated class responsible for
/// all Vector based mathematics in 4 dimensions. It is commonly
/// used throughout the engine for a variety of different tasks,
/// such as setting the elements within matrices.
///
/// sparky::Vector4<T> also contains the most common mathematics
/// and algorithms associated with Vectors, such as the dot 
/// product and normalisation.
///
////////////////////////////////////////////////////////////