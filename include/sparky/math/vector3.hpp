#ifndef __SPARKY_VECTOR3_HPP__
#define __SPARKY_VECTOR3_HPP__

namespace sparky
{
	template <typename T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;

	public:
		explicit Vector3(void);
		explicit Vector3(const T x, const T y, const T z);
		~Vector3(void) = default;
	};

	#include <sparky\math\vector3.inl>

	typedef Vector3<unsigned int> Vector3u;
	typedef Vector3<int> Vector3i;
	typedef Vector3<float> Vector3f;
}

#endif//__SPARKY_VECTOR3_HPP__