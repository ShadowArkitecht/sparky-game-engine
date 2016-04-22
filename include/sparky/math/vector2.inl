////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>::Vector2(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0))
{
}

////////////////////////////////////////////////////////////
template <typename T>
Vector2<T>::Vector2(const T x, const T y)
	: x(x), y(y)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U>& vector)
	: x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y))
{
}