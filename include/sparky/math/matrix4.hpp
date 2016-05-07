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

#ifndef __SPARKY_MATRIX4_HPP__
#define __SPARKY_MATRIX4_HPP__

#include <cmath>
/*
====================
Class Includes
====================
*/
#include <sparky\math\vector3.hpp>		// Vector3's needed as parameters.
#include <sparky\math\vector4.hpp>		// Rows and columns of the matrix returns Vector4's.
#include <sparky\math\mathutils.hpp>	// Conversion of radians and degrees.

namespace sparky
{
	template <typename T>
	class Matrix4 final
	{
	public:
		/*
		====================
		Member Variables
		====================
		*/
		T m[4][4];	// Raw information of the matrix.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a default Matrix4 Object.
		///
		/// When the default constructor of Matrix4 is used to instantiate
		/// an object. it is set to the identity matrix.
		/// [ 1, 0, 0, 0 ]
		/// [ 0, 1, 0, 0 ]
		/// [ 0, 0, 1, 0 ]
		/// [ 0, 0, 0, 1 ]
		///
		////////////////////////////////////////////////////////////
		explicit Matrix4(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Matrix4 Object with rows.
		/// 
		/// Constructs a Matrix4 from the rows passed in as Vector4
		/// objects.
		/// 
		/// \param first	The first row.
		/// \param second	The second row.
		/// \param third	The third row.
		/// \param fourth	The fourth row.
		///
		////////////////////////////////////////////////////////////
		explicit Matrix4(const Vector4<T>& first, const Vector4<T>& second, const Vector4<T>& third, const Vector4<T>& fourth);

		////////////////////////////////////////////////////////////
		/// \breif Default destruction of the Matrix4 object.
		////////////////////////////////////////////////////////////
		~Matrix4(void) = default;

		/*
		====================
		Operators
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Performs a member-wise multiplication of two matrices.
		///
		/// Multiplication is applied between two different matrices with
		/// the result being assigned to a new Matrix object. It is important
		/// to remember that matrices are non-communative.
		///
		/// \param matrix		The matrix to be multiplied by.
		///
		/// \retval Matrix4		A Matrix4 object of the multiplication.
		///
		////////////////////////////////////////////////////////////
		Matrix4 operator*(const Matrix4& matrix) const;

		////////////////////////////////////////////////////////////
		/// \brief Performs a member-wise multiplication of two matrices.
		///
		/// Multiplication is applied between two different matrices with
		/// the result being assigned to this Matrix4. It is important
		/// to remember that matrices are non-communative.
		///
		/// \param matrix		The matrix to be multiplied by.
		///
		/// \retval Matrix4		A reference to this.
		///
		////////////////////////////////////////////////////////////
		const Matrix4& operator*=(const Matrix4& matrix);

		////////////////////////////////////////////////////////////
		/// \brief Assignment operator. Sets one matrix to another.
		///
		/// \param matrix	The matrix to set the object to.
		///
		/// \param Matrix4	A reference to this object.
		///
		////////////////////////////////////////////////////////////
		Matrix4& operator=(const Matrix4& matrix);

		////////////////////////////////////////////////////////////
		/// \brief Overload the output stream operator to print a matrix
		///        to the console window.
		///
		/// This method can be used for debugging processes to print a
		/// matrix to the console window. The matrix will be printed in the
		/// following format:
		///
		/// [ 0, 0, 0, 0 ]
		/// [ 0, 0, 0, 0 ]
		/// [ 0, 0, 0, 0 ]
		/// [ 0, 0, 0, 0 ]
		///
		/// \param os		The output stream to stream into.
		/// \param matrix	The matrix to print to the console window.
		///
		/// \retval ostream	The stream of the object.
		///
		////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				os << matrix.getRow(i) << std::endl;
			}

			return os;
		}

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the row of the Matrix at the specified index.
		/// 
		/// \param index	The row index.
		///
		/// \retval Vector3	A Vector4 containing the information of the Matrix row.
		///
		////////////////////////////////////////////////////////////
		Vector4<T> getRow(const unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the row of the Matrix at the specified index.
		/// 
		/// \param index	The row index.
		/// \param row		The Vector4 to set the row to.
		///
		////////////////////////////////////////////////////////////
		void setRow(const unsigned int index, const Vector4<T>& row);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the column of the Matrix at the specified index.
		/// 
		/// \param index	The column index.
		///
		/// \retval Vector3	A Vector4 containing the information of the Matrix column.
		///
		////////////////////////////////////////////////////////////
		Vector4<T> getColumn(const unsigned int index) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the column of the Matrix at the specified index.
		/// 
		/// \param index	The column index.
		/// \param row		The Vector4 to set the row to.
		///
		////////////////////////////////////////////////////////////
		void setColumn(const unsigned int index, const Vector4<T>& column);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a yaw rotation matrix.
		///
		/// Constructs a yaw rotation matrix with the applied number of degrees.
		///	When a matrix is multiplied by the yaw rotation matrix, it will alter 
		///  the object's rotation on the local z axis.
		///
		/// [ cos(theta) -sinf(theta) 0 0 ]
		/// [ sin(theta)  cosf(theta) 0 0 ]
		/// [ 0			  0			  1 0 ]
		/// [ 0			  0			  0 1 ]
		/// 
		/// \param degrees		The degrees to apply to the rotation matrix.
		///
		/// \retval Matrix4		The yaw rotation matrix constructed with the degrees.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 yawRotation(const T degrees);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a pitch rotation matrix
		///
		/// Constructs a yaw rotation matrix with the applied number of degrees.
		/// When a matrix is multiplied by the pitch rotation matrix, it will alter 
		/// the object's rotation on the local y axis.
		///
		/// [  cos(theta)  0 sin(theta) 0 ]
		/// [  0           1 0          0 ]
		/// [ -sin(theta)  0 cos(theta) 0 ]
		/// [  0		   0 0          1 ]
		/// 
		/// \param degrees		The degrees to apply to the rotation matrix.
		/// \retval Matrix4		The pitch rotation matrix constructed with the degrees.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 pitchRotation(const T degrees);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a roll rotation matrix.
		///
		/// Constructs a roll rotation matrix with the applied number of degrees.
		/// When a matrix is multiplied by the roll rotation matrix, it will alter
		/// the object's rotation on the local x axis.
		///
		/// [  1 0          0           0 ]
		/// [  0 cos(theta) -sin(theta) 0 ]
		/// [  0 sin(theta)  cos(theta) 0 ]
		/// [  0 0          0           1 ]
		/// 
		/// \param degrees		The degrees to apply to the rotation matrix.
		///
		/// \retval Matrix4		The roll rotation matrix constructed with the degrees.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rollRotation(const T degrees);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a translation Matrix.
		///
		/// Constructs an identity matrix and then sets the translation column
		/// to the position parameter. When a matrix is multiplied by the 
		/// translation matrix, it will alter the object's position in 3D space.
		///
		/// [ 1 0 0 position.x ]
		/// [ 0 1 0 position.y ]
		/// [ 0 0 1 position.z ]
		/// [ 0 0 0 1          ]
		/// 
		/// \param position		The position to set the translation matrix to.
		/// \retval Matrix4		A translation matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 translation(const Vector3<T>& position);

		////////////////////////////////////////////////////////////
		/// \brief Sets the x, y, and z rotation of a Matrix.
		///
		/// Convenience method for quickly setting the x, y and z rotation of a
		/// Matrix. The corresponding components of the rotation Vector set the roll,
		/// yaw and pitch rotational degrees respectively.
		/// 
		/// \param rotation		The rotation to apply to the Matrix.
		///
		/// \retval	Matrix4		The rotated matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rotation(const Vector3<T>& rotation);

		////////////////////////////////////////////////////////////
		/// \brief Construct a rotation Matrix with right, up and forward Vectors.
		///
		/// Convenience method for setting the rows and elements of rotation within
		/// the matrix. The rows of the matrix are set with the right, up and 
		/// forward Vector parameters.
		/// 
		/// \param right	The right rotation.
		/// \param up		The up rotation.
		/// \param forward  The forward rotation.
		///
		/// \retval Matrix4 The rotated Matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 rotation(const Vector3<T>& right, const Vector3<T>& up, const Vector3<T>& forward);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a scale Matrix.
		///
		/// Creates a indentity matrix and then scales the matrix on 
		/// the x, y and z axis by using the members from the corresponding
		/// scale Vector parameter.
		///
		/// [ scale.x 0       0       0 ]
		/// [ 0       scale.y 0       0 ]
		/// [ 0       0       scale.z 0 ]
		/// [ 0       0       0       1 ]
		/// 
		/// \param scale		The vector to scale the matrix by.
		///
		/// \retval Matrix4		The scale Matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 scale(const Vector3<T>& scale);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a projection Matrix.
		///
		/// Constructs a projection Matrix. A projection matrix is responsible
		/// for projecting 3D points (such as vectors) that; when multiplied by camera 
		/// space, are projected onto the screen buffer in the correct positions.
		/// 
		/// \param fov				The Field of View.
		/// \param aspectRatio		The aspect ratio.
		/// \param near				The near-clipping plane.
		/// \param far				The far-clipping plane.
		///
		/// \retval Matrix4			The projection Matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 projection(const T fov, const T aspectRatio, const T zNear, const T zFar);

		////////////////////////////////////////////////////////////
		/// \brief Creates a perspective Matrix.
		///
		/// Creates a perspective Matrix with the specified forward and up vector.
		/// 
		/// \param forward		The forward vector.
		/// \param up			The up vector.
		///
		/// \retval Matrix4		The perspective Matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 perspective(const Vector3<T>& forward, const Vector3<T>& up);

		////////////////////////////////////////////////////////////
		/// \brief Creates a matrix that is the transpose of the parameter.
		///
		/// A transposed matrix is a matrix that has the columns switched
		/// with the rows. This new matrix is returned as the result to this 
		/// function.
		///
		/// \retval Matrix4		The transposed Matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 transpose(const Matrix4& matrix);

		/*
		====================
		Properties
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs an Identity Matrix.
		///
		/// This is a matrix that effectively does nothing when multiplied. It has 1s 
		/// in the main diagonal and 0s in all other elements.
		///
		/// [ 1 0 0 0 ]
		/// [ 0 1 0 0 ]
		/// [ 0 0 1 0 ]
		/// [ 0 0 0 1 ]
		/// 
		/// \retval Matrix4		A Matrix4 identity.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 identity(void);

		////////////////////////////////////////////////////////////
		/// \brief Constructs a Matrix4 with all elements set to 0.
		///
		/// [ 0 0 0 0 ]
		/// [ 0 0 0 0 ]
		/// [ 0 0 0 0 ]
		/// [ 0 0 0 0 ]
		/// 
		/// \retval Matrix4		A 'zeroed' Matrix.
		///
		////////////////////////////////////////////////////////////
		static Matrix4 zero(void);
	};

#include <sparky\math\matrix4.inl>

	typedef Matrix4<int> Matrix4i;
	typedef Matrix4<float> Matrix4f;

}//namespace sparky

#endif//__SPARKY_MATRIX4_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Matrix4<T>
/// \ingroup math
///
/// sparky::Matrix4 is the underlying rotational matrices that
/// the sparky engine utilises. The matrices are used to rotate
/// objects within GLSL shaders and for communication with OpenGL.
/// 
/// The matrices are never directed accessed by the user, instead
/// all rotation within the application utilises Quaternions, which
/// are converted into matrices before application. Below is a code 
/// example of using the Matrices.
///
/// \code
/// // Create a matrix object.
/// sparky::Matrix4f matrix;
///
/// // Set the matrix to equal a random translation, rotation and scale.
/// matrix *= Matrix4f::scale(Vector3f::one());
/// // Rotates the matrix 50 degrees on the y axis.
/// matrix *= Matrix4f::rotation(Vector3f(0.0f, 50.0f, 0.0f));
///
/// matrix *= Matrix4f::translation(Vector3f(0.0f, 0.0f, 7.0f);
///
////////////////////////////////////////////////////////////