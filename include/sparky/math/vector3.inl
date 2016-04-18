template <typename T>
Vector3<T>::Vector3(void)
	: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
{
}

template <typename T>
Vector3<T>::Vector3(const T x, const T y, const T z)
	: x(x), y(y), z(z)
{
}