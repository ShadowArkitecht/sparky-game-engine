template <typename T>
Vector2<T>::Vector2(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0))
{
}

template <typename T>
Vector2<T>::Vector2(const T x, const T y)
	: x(x), y(y)
{
}