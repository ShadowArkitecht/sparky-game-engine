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
Quaternion<T>::Quaternion(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(1))
{
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w)
	: x(x), y(y), z(z), w(w)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Quaternion<T>::Quaternion(const Quaternion<U>& quaternion)
	: x(static_cast<T>(quaternion.x)), y(static_cast<T>(quaternion.y)), z(static_cast<T>(quaternion.z)), w(static_cast<T>(quaternion.w))
{
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T>::Quaternion(const Matrix4<T>& matrix)
{
	T trace = matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2];

	if (trace > 0)
	{
		T root = static_cast<T>(0.5 / sqrt(trace + 1));

		w = static_cast<T>(0.25) / root;
		x = (matrix.m[2][1] - matrix.m[1][2]) * root;
		y = (matrix.m[0][2] - matrix.m[2][0]) * root;
		z = (matrix.m[1][0] - matrix.m[0][1]) * root;
	}

	else if ((matrix.m[0][0] > matrix.m[1][1]) && (matrix.m[0][0] > matrix.m[2][2]))
	{
		T root = 2 * static_cast<T>(sqrt(1.0f + matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2]));

		w = (matrix.m[2][1] - matrix.m[1][2]) / root;
		x = static_cast<T>(0.25) * root;
		y = (matrix.m[0][1] + matrix.m[1][0]) / root;
		z = (matrix.m[0][2] + matrix.m[2][0]) / root;
	}

	else if (matrix.m[1][1] > matrix.m[2][2])
	{
		T root = 2 * static_cast<T>(sqrt(1.0f + matrix.m[1][1] - matrix.m[0][0] - matrix.m[2][2]));

		w = (matrix.m[0][2] - matrix.m[2][0]) / root;
		x = (matrix.m[0][1] + matrix.m[1][0]) / root;
		y = static_cast<T>(0.25f) * root;
		z = (matrix.m[1][2] + matrix.m[2][1]) / root;
	}

	else
	{
		T root = 2 * static_cast<T>(sqrt(1.0f + matrix.m[2][2] - matrix.m[0][0] - matrix.m[1][1]));

		w = (matrix.m[1][0] - matrix.m[0][1]) / root;
		x = (matrix.m[0][2] + matrix.m[2][0]) / root;
		y = (matrix.m[1][2] + matrix.m[2][1]) / root;
		z = static_cast<T>(0.25) * root;
	}
}

/*
====================
Operators
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& quaternion) const
{
	Quaternion<T> result = *this;

	result.w = (w * quaternion.w) - (x * quaternion.x) - (y * quaternion.y) - (z * quaternion.z);
	result.x = (x * quaternion.w) + (w * quaternion.x) + (y * quaternion.z) - (z * quaternion.y);
	result.y = (y * quaternion.w) + (w * quaternion.y) + (z * quaternion.x) - (x * quaternion.z);
	result.z = (z * quaternion.w) + (w * quaternion.z) + (x * quaternion.y) - (y * quaternion.x);

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::operator*(const Vector3<T>& vector) const
{
	Quaternion<T> result = *this;

	result.w = (-x * vector.x) - (y * vector.y) - (z * vector.z);
	result.x = ( w * vector.x) + (y * vector.z) - (z * vector.y);
	result.y = ( w * vector.y) + (z * vector.x) - (x * vector.z);
	result.z = ( w * vector.z) + (x * vector.y) - (y * vector.x);

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::operator/(const Quaternion<T>& quaternion) const
{
	Quaternion<T> result = *this;

	result.x = x / quaternion.x;
	result.y = y / quaternion.y;
	result.z = z / quaternion.z;
	result.w = w / quaternion.w;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::operator/(const T value) const
{
	return operator/(Quaternion<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& quaternion)
{
	w = (w * quaternion.w) - (x * quaternion.x) - (y * quaternion.y) - (z * quaternion.z);
	x = (x * quaternion.w) + (w * quaternion.x) + (y * quaternion.z) - (z * quaternion.y);
	y = (y * quaternion.w) + (w * quaternion.y) + (z * quaternion.x) - (x * quaternion.z);
	z = (z * quaternion.w) + (w * quaternion.z) + (x * quaternion.y) - (y * quaternion.x);

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Quaternion<T>& Quaternion<T>::operator*=(const Vector3<T>& vector)
{
	w = (-x * vector.x) - (y * vector.y) - (z * vector.z);
	x = ( w * vector.x) + (y * vector.z) - (z * vector.y);
	y = ( w * vector.y) + (z * vector.x) - (x * vector.z);
	z = ( w * vector.z) + (x * vector.y) - (y * vector.x);

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Quaternion<T>& Quaternion<T>::operator/=(const Quaternion& quaternation)
{
	x /= quaternion.x;
	y /= quaternion.y;
	z /= quaternion.z;
	w /= quaternion.w;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Quaternion<T>& Quaternion<T>::operator/=(const T value)
{
	return operator/=(Quaternion<T>(value, value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
bool Quaternion<T>::operator==(const Quaternion& quaternion)
{
	return (x == quaternion.x && y == quaternion.y && z == quaternion.z && w == quaternion.w);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Quaternion<T>::operator!=(const Quaternion& quaternion)
{
	return !(*this == quaternion);
}

/*
====================
Methods
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
T Quaternion<T>::magnitudeSqr(void) const
{
	return ((w * w) + (x * x) + (y * y) + (z * z));
}

////////////////////////////////////////////////////////////
template <typename T>
T Quaternion<T>::magnitude(void) const
{
	return static_cast<T>(sqrt(magnitudeSqr()));
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::normalised(void) const
{
	return *this / magnitude();
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::conjugate(void) const
{
	return Quaternion<T>(-x, -y, -z, w);
}

////////////////////////////////////////////////////////////
template <typename T>
Matrix4<T> Quaternion<T>::toMatrix(void) const
{
	Vector3<T> r = Vector3<T>(1 - 2 * ((y * y) + (z * z)), 2 * ((x * y) - (z * w)), 2 * ((x * z) + (y * w)));
	Vector3<T> u = Vector3<T>(2 * ((x * y) + (z * w)), 1 - 2 * ((x * x) + (z * z)), 2 * ((y * z) - (x * w)));
	Vector3<T> f = Vector3<T>(2 * ((x * z) - (y * w)), 2 * ((y * z) + (x * w)), 1 - 2 * ((x * x) + (y * y)));

	return Matrix4<T>::rotation(r, u, f);
}

////////////////////////////////////////////////////////////
template <typename T>
T Quaternion<T>::dot(const Quaternion<T>& u, const Quaternion<T>& v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w));
}

////////////////////////////////////////////////////////////
template <typename T>
T Quaternion<T>::angle(const Quaternion<T>& from, const Quaternion<T>& to)
{
	T dot = Quaternion<T>::dot(from, to);
	T mag = from.magnitude() * to.magnitude();

	T angle = static_cast<T>(acos(dot / mag));

	return radiansToDegrees<T>(angle);
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::angleAxis(const Vector3<T>& axis, const T angle)
{
	T sinAngle = static_cast<T>(sin(MathUtils<T>::toRadians(angle / 2)));
	T cosAngle = static_cast<T>(cos(MathUtils<T>::toRadians(angle / 2)));

	return Quaternion<T>(axis.x * sinAngle, axis.y * sinAngle, axis.z * sinAngle, cosAngle).normalised();
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::lookRotation(const Vector3<T>& target)
{
	return Quaternion<T>(Matrix4<T>::perspective(target, Vector3<T>::up()));
}

/*
====================
Properties
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::identity(void)
{
	return Quaternion<T>();
}

////////////////////////////////////////////////////////////
template <typename T>
Quaternion<T> Quaternion<T>::zero(void)
{
	return Quaternion<T>(0, 0, 0, 0);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Quaternion<T>::right(void) const
{
	//return Vector3<T>::right().rotate(*this);
	Quaternion<T> rot = *this;
	Quaternion<T> result = rot.normalised() * Vector3<T>::right() * rot.normalised().conjugate();

	return Vector3<T>(result.x, result.y, result.z);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Quaternion<T>::up(void) const
{
	//return Vector3<T>::up().rotate(*this);
	Quaternion<T> rot = *this;
	Quaternion<T> result = rot.normalised() * Vector3<T>::up() * rot.normalised().conjugate();

	return Vector3<T>(result.x, result.y, result.z);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Quaternion<T>::forward(void) const
{
	//return Vector3<T>::forward().rotate(*this);
	Quaternion<T> rot = *this;
	Quaternion<T> result = rot.normalised() * Vector3<T>::forward() * rot.normalised().conjugate();

	return Vector3<T>(result.x, result.y, result.z);
}