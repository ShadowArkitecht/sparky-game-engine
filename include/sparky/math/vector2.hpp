#ifndef __SPARKY_VECTOR2_HPP__
#define __SPARKY_VECTOR2_HPP__

namespace sparky
{
	template <typename T>
	class Vector2 final
	{
	public:
		T x;
		T y;

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit Vector2(void);
		explicit Vector2(const T x, const T y);
		template <typename U>
		explicit Vector2(const Vector2<U>& vector);
		~Vector2(void) = default;
	};

	#include <sparky\math\vector2.inl>

	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;

}//namespace sparky

#endif//__SPARKY_VECTOR2_HPP__