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
Ctor and Dtor
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T>::Matrix4(void)
{
	setRow(0, Vector4<T>(1, 0, 0, 0));
	setRow(1, Vector4<T>(0, 1, 0, 0));
	setRow(2, Vector4<T>(0, 0, 1, 0));
	setRow(3, Vector4<T>(0, 0, 0, 1));
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T>::Matrix4(const Vector4<T>& first, const Vector4<T>& second, const Vector4<T>& third, const Vector4<T>& fourth)
{
	setRow(0, first);
	setRow(1, second);
	setRow(2, third);
	setRow(3, fourth);
}

/*
====================
Operators
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& matrix) const
{
	Matrix4<T> result = *this;

	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			result.m[i][j] = m[i][0] * matrix.m[0][j] +
							 m[i][1] * matrix.m[1][j] +
							 m[i][2] * matrix.m[2][j] +
							 m[i][3] * matrix.m[3][j];
		}
	}

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
const Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& matrix)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			m[i][j] = m[i][0] * matrix.m[0][j] +
					  m[i][1] * matrix.m[1][j] +
					  m[i][2] * matrix.m[2][j] +
					  m[i][3] * matrix.m[3][j];
		}
	}

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& matrix)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			m[i][j] = matrix.m[i][j];
		}
	}

	return *this;
}

/*
====================
Getters and Setters
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Matrix4<T>::getRow(const unsigned int index) const
{
	return Vector4<T>(m[0][index], m[1][index], m[2][index], m[3][index]);
}

////////////////////////////////////////////////////////////
template <typename T>
void Matrix4<T>::setRow(const unsigned int index, const Vector4<T>& row)
{
	m[0][index] = row.x;
	m[1][index] = row.y;
	m[2][index] = row.z;
	m[3][index] = row.w;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector4<T> Matrix4<T>::getColumn(const unsigned int index) const
{
	return Vector4<T>(m[index][0], m[index][1], m[index][2], m[index][3]);
}

////////////////////////////////////////////////////////////
template <typename T>
void Matrix4<T>::setColumn(const unsigned int index, const Vector4<T>& column)
{
	m[index][0] = column.x;
	m[index][1] = column.y;
	m[index][2] = column.z;
	m[index][3] = column.w;
}

/*
====================
Methods
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::yawRotation(const T degrees)
{
	const T theta = MathUtils<T>::toRadians(degrees);
	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(cos(theta), -sin(theta), 0, 0));
	matrix.setRow(1, Vector4<T>(sin(theta),  cos(theta), 0, 0));
	matrix.setRow(2, Vector4<T>(0, 0, 1, 0));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::pitchRotation(const T degrees)
{
	const T theta = MathUtils<T>::toRadians(degrees);

	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(cos(theta), 0, sin(theta), 0));
	matrix.setRow(1, Vector4<T>(0, 1, 0, 0));
	matrix.setRow(2, Vector4<T>(-sin(theta), 0, cos(theta), 0));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::rollRotation(const T degrees)
{
	const T theta = MathUtils<T>::toRadians(degrees);

	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(1, 0, 0, 0));
	matrix.setRow(1, Vector4<T>(0, cos(theta), -sin(theta), 0));
	matrix.setRow(2, Vector4<T>(0, sin(theta),  cos(theta), 0));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::translation(const Vector3<T>& position)
{
	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(1, 0, 0, position.x));
	matrix.setRow(1, Vector4<T>(0, 1, 0, position.y));
	matrix.setRow(2, Vector4<T>(0, 0, 1, position.z));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::rotation(const Vector3<T>& rotation)
{
	Matrix4<T> matrix;

	Matrix4<T> roll = rollRotation(rotation.x);
	Matrix4<T> pitch = pitchRotation(rotation.y);
	Matrix4<T> yaw = yawRotation(rotation.z);

	matrix = yaw * pitch * roll;

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::rotation(const Vector3<T>& right, const Vector3<T>& up, const Vector3<T>& forward)
{
	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(right.x, right.y, right.z, 0));
	matrix.setRow(1, Vector4<T>(up.x, up.y, up.z, 0));
	matrix.setRow(2, Vector4<T>(forward.x, forward.y, forward.z, 0));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::scale(const Vector3<T>& scale)
{
	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(scale.x, 0, 0, 0));
	matrix.setRow(1, Vector4<T>(0, scale.y, 0, 0));
	matrix.setRow(2, Vector4<T>(0, 0, scale.z, 0));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::projection(const T fov, const T aspectRatio, const T zNear, const T zFar)
{
	T tanHalfFoV = static_cast<T>(tan(MathUtils<T>::toRadians(fov / 2)));
	T range = zNear - zFar;

	Matrix4<T> matrix = Matrix4<T>::identity();

	matrix.setRow(0, Vector4<T>(1 / (tanHalfFoV * aspectRatio), 0, 0, 0));
	matrix.setRow(1, Vector4<T>(0, 1 / tanHalfFoV, 0, 0));
	matrix.setRow(2, Vector4<T>(0, 0, (-zNear - zFar) / range, 2 * zFar * zNear / range));
	matrix.setRow(3, Vector4<T>(0, 0, 1, 0));

	return matrix;
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::perspective(const Vector3<T>& forward, const Vector3<T>& up)
{
	Vector3<T> f = forward.normalised();
	Vector3<T> u = up.normalised();

	u = Vector3<T>::cross(u, f);
	Vector3<T> v = Vector3<T>::cross(f, u);

	Matrix4<T> matrix;

	matrix.setRow(0, Vector4<T>(u.x, u.y, u.z, 0));
	matrix.setRow(1, Vector4<T>(v.x, v.y, v.z, 0));
	matrix.setRow(2, Vector4<T>(f.x, f.y, f.z, 0));
	matrix.setRow(3, Vector4<T>(0, 0, 0, 1));

	return matrix;
}

/*
====================
Properties
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::identity(void)
{
	return Matrix4<T>();
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Matrix4<T>::zero(void)
{
	Matrix4<T> matrix;

	for (unsigned int i = 0; i < 4; i++)
	{
		matrix.setRow(i, Vector4<T>());
	}

	return matrix;
}