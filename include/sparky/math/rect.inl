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
Rect<T>::Rect(void)
	: position(), size()
{
}

////////////////////////////////////////////////////////////
template <typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size)
	: position(position), size(size)
{
}

////////////////////////////////////////////////////////////
template <typename T>
Rect<T>::Rect(const T x, const T y, const T width, const T height)
	: position(x, y), size(width, height)
{
}

////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rect)
	: position(rect.position), size(rect.size)
{
}

/*
====================
Getters and Setters
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::operator==(const Rect<T>& rect)
{
	return (position.x == rect.position.x) && (position.y == rect.position.y) &&
		   (size.x == rect.size.x) && (size.y == rect.size.y);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::operator!=(const Rect<T>& rect)
{
	return !(*this == rect);
}

/*
====================
Methods
====================
*/
////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::contains(const Vector2<T>& point) const
{
	// Calculate min points
	Vector2<T> mininum(std::min<T>(position.x, position.x + size.x), 
					   std::min<T>(position.y, position.y + size.y));

	// Calculate max points
	Vector2<T> maximum(std::max<T>(position.x, position.x + size.x),
					   std::max<T>(position.y, position.y + size.y));

	return (point.x >= mininum.x) && (point.x <= maximum.x) && (point.y >= mininum.y) && (point.y <= maximum.y);
}

////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::contains(const T x, const T y) const
{
	return this->contains(Vector2<T>(x, y));
}

////////////////////////////////////////////////////////////
template <typename T>
bool Rect<T>::collides(const Rect<T>& rect) const
{
	// Create the min and max of the first Rectangle.
	Vector2<T> minRect1(std::min<T>(position.x, position.x + size.x),
						std::min<T>(position.y, position.y + size.y));

	Vector2<T> maxRect1(std::max<T>(position.x, position.x + size.x),
						std::max<T>(position.y, position.y + size.y));

	// Create the min and max of the second Rectangle.
	Vector2<T> minRect2(std::min<T>(rect.position.x, rect.position.x + rect.size.x),
						std::min<T>(rect.position.y, rect.position.y + rect.size.y));

	Vector2<T> maxRect2(std::max<T>(rect.position.x, rect.position.x + rect.size.x),
						std::max<T>(rect.position.y, rect.position.y + rect.size.y));

	// Create the intersection points
	T left =  std::max<T>(minRect1.x, minRect2.x);
	T top =	  std::max<T>(minRect1.y, minRect2.y);
	T right = std::min<T>(maxRect1.x, maxRect2.x);
	T bottom =std::min<T>(maxRect1.y, maxRect2.y);

	return ((left < right) && (top < bottom));
}