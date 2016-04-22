/*
====================
Ctor and Dtor
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>::Vector3(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T>::Vector3(const T x, const T y, const T z)
	: x(x), y(y), z(z)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Vector3<T>::Vector3(const Vector3<U>& vector)
	: x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)), z(static_cast<T>(vector.z))
{
}

/*
====================
Operators
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x + vector.x;
	result.y = y + vector.y;
	result.z = z + vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator+(const T value) const
{
	return operator+(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x - vector.x;
	result.y = y - vector.y;
	result.z = z - vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator-(const T value) const
{
	return operator-(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x * vector.x;
	result.y = y * vector.y;
	result.z = z * vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator*(const T value) const
{
	return operator*(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& vector) const
{
	Vector3<T> result = *this;

	result.x = x / vector.x;
	result.y = y / vector.y;
	result.z = z / vector.z;

	return result;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator/(const T value) const
{
	return operator/(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator+=(const T value)
{
	return operator+=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator-=(const T value)
{
	return operator-=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator*=(const T value)
{
	return operator*=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;

	return *this;
}

////////////////////////////////////////////////////////////
template <typename T>
const Vector3<T>& Vector3<T>::operator/=(const T value)
{
	return operator/=(Vector3<T>(value, value, value));
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector3<T>::operator==(const Vector3<T>& vector) const
{
	return (x == vector.x) && (y == vector.y) && (z == vector.z);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Vector3<T>::operator!=(const Vector3<T>& vector) const
{
	return !(*this == vector);
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::operator-(void) const
{
	return Vector3<T>(-x, -y, -z);
}

/*
====================
Methods
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::magnitudeSqr(void) const
{
	return ((x * x) + (y * y) + (z * z));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::magnitude(void) const
{
	return static_cast<T>(sqrt(magnitudeSqr()));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::normalised(void) const
{
	return *this / magnitude();
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::dot(const Vector3<T>& u, const Vector3<T>& v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& u, const Vector3<T>& v)
{
	return Vector3<T>((u.y * v.z) - (u.z * v.y),
					  (u.z * v.x) - (u.x * v.z),
					  (u.x * v.y) - (u.y * v.x));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::angle(const Vector3<T>& from, const Vector3<T>& to)
{
	T dot = Vector3<T>::dot(from, to);
	T mag = from.magnitude() * to.magnitude();

	T angle = static_cast<T>(acos(dot / mag));

	const T PI = static_cast<T>(3.14f);

	return angle * (static_cast<T>(180.0f) / PI);
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::distanceSqr(const Vector3<T>& from, const Vector3<T>& to)
{
	return ((to.x - from.x) * (to.x - from.x)) + ((to.y - from.y) * (to.y - from.y)) + ((to.z - from.z) * (to.z - from.z));
}

////////////////////////////////////////////////////////////
template <typename T>
T Vector3<T>::distance(const Vector3<T>& from, const Vector3<T>& to)
{
	return static_cast<T>(sqrt(distanceSqr(from, to)));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::minimum(const Vector3<T>& u, const Vector3<T>& v)
{
	return Vector3<T>(std::min(u.x, v.x), std::min(u.y, v.y), std::min(u.z, v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::maximum(const Vector3<T>& u, const Vector3<T>& v)
{
	return Vector3<T>(std::max(u.x, v.x), std::max(u.y, v.y), std::max(u.z, v.z));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::moveTowards(const Vector3<T>& current, const Vector3<T>& target, const T speed)
{
	return (current - target).normalised() * speed;
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::lerp(const Vector3<T>& current, const Vector3<T>& target, const T speed)
{
	Vector3<T> cur = current * speed;
	Vector3<T> tar = target * (static_cast<T>(1) - speed);

	return cur + tar;
}

/*
====================
Properties
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::zero(void)
{
	return Vector3<T>();
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::one(void)
{
	return Vector3<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::right(void)
{
	return Vector3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::up(void)
{
	return Vector3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
}

////////////////////////////////////////////////////////////
template <typename T>
Vector3<T> Vector3<T>::forward(void)
{
	return Vector3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}