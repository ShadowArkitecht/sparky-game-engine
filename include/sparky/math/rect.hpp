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

#ifndef __SPARKY_RECT_HPP__
#define __SPARKY_RECT_HPP__

/*
====================
CPP Includes
====================
*/
#include <algorithm>
/*
====================
Class Includes
====================
*/
#include <sparky\math\vector2.hpp>		// Rect is constructed of two vector objects.

namespace sparky
{
	template <typename T>
	class Rect final
	{
	public:
		/*
		====================
		Member Variables
		====================
		*/
		Vector2<T> position;	// The position of the Rectangle.
		Vector2<T> size;		// The dimensions of the Rectangle.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of a Rect object.
		///
		/// Creates a Rectangle shape that has no position or size. 
		/// This constructor is the equivalent to creating an empty
		/// rectangle [ 0, 0, 0, 0 ].
		///
		////////////////////////////////////////////////////////////
		explicit Rect(void);

		////////////////////////////////////////////////////////////
		/// \brief Creates a rectangle shape with a defined position and size.
		///
		/// Creates a Rectangle shape with a specified position and 
		/// size. This is equivalent to [ p.x, p.y, s.x, s.y ].
		///
		/// \param position		The position of the Rectangle.
		/// \param size			The dimensions of the Rectangle.
		///
		////////////////////////////////////////////////////////////
		explicit Rect(const Vector2<T>& position, const Vector2<T>& size);

		////////////////////////////////////////////////////////////
		/// \brief Creates a rectangle with individual position and size.
		///
		/// This is equivalent to the previous constructor, except that
		/// the values are set individually, instead of utilising vectors.
		///
		/// \param x		The x position of the Rectangle.
		/// \param y		The y position of the Rectangle.
		/// \param width	The width of the Rectangle.
		/// \param height	The height of the Rectangle.
		///
		////////////////////////////////////////////////////////////
		explicit Rect(const T x, const T y, const T width, const T height);

		////////////////////////////////////////////////////////////
		/// \brief Creates a rectangle from the parameters of a different
		///		   rectangle.
		///
		/// \param rect		The different rect to get the values from.
		///
		////////////////////////////////////////////////////////////
		template <typename U>
		explicit Rect(const Rect<U>& rect);

		////////////////////////////////////////////////////////////
		/// \brief	Destruction of the Rectangle object.
		////////////////////////////////////////////////////////////
		~Rect(void) = default;

		/*
		====================
		Operators
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Comparison operator between two Rectangle objects.
		///
		/// \retval bool	True if the Rectangles are at the same position
		///					and dimensions.
		///
		////////////////////////////////////////////////////////////
		bool operator==(const Rect<T>& rect);

		////////////////////////////////////////////////////////////
		/// \brief Comparison operator between two Rectangle objects.
		///
		/// \retval bool	True if the Rectangles are not at the same position
		///					and dimensions.
		///
		////////////////////////////////////////////////////////////
		bool operator!=(const Rect<T>& rect);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Checks if a point is within the Rectangle.
		///
		/// Simple 2D axis aligned box to point collision. It checks
		/// to see if the point is contained within the current 
		/// Rectangle object.
		///
		/// \param point	The point to check within the Rectangle.
		///
		/// \retval bool	True if the point is within the Rectangle,
		///					False if not.
		///
		////////////////////////////////////////////////////////////
		bool contains(const Vector2<T>& point) const;

		////////////////////////////////////////////////////////////
		/// \brief Checks if a point is within the Rectangle.
		///
		/// Simple 2D axis aligned box to point collision. It checks
		/// to see if the point is contained within the current 
		/// Rectangle object.
		///
		/// \param x		The x point to check within the Rectangle.
		/// \param y		The y point to check within the Rectangle.
		///
		/// \retval bool	True if the point is within the Rectangle,
		///					False if not.
		///
		////////////////////////////////////////////////////////////
		bool contains(const T x, const T y) const;

		////////////////////////////////////////////////////////////
		/// \brief Basic AABB Collision between two Rectangles.
		///
		/// This method checks for collision between two different
		/// Rectangle objects.
		///
		/// \param rect		The Rectangle to compare against.
		///
		////////////////////////////////////////////////////////////
		bool collides(const Rect<T>& rect) const;
	};

	#include <sparky\math\rect.inl>

	/*
	====================
	Type definitions
	====================
	*/
	typedef Rect<int> Recti;
	typedef Rect<unsigned int> Rectu;
	typedef Rect<float> Rectf;

}//namespace sparky

#endif//__SPARKY_RECT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Rect<T>
/// \ingroup math
///
/// sparky::Rect<T> is a templated class for creating basic 
/// Rectangle shapes and testing basic collision for Rectangle
/// objects.
///
/// sparky::Rect<T> can be used in conjunction with sparky::IMeshComponent
/// to create HUD elements or 2D sprites. Below is a code example of using
/// one of the type defined conveniences Rects.
///
/// \code
/// // Create a Rectangle.
/// sparky::Rectf rect(0.0f, 0.0f, 10.0f, 10.0f);
///
/// // Create a point to test if it intersects with the Rectangle.
/// Vector2f point(5.0f, 5.0f);
///
/// // Test if point intersects with Rectangle (spoiler alert: it does).
/// if (rect.contains(point))
/// {
///		std::cout << "The point is inside the Rectangle!" << std::endl;
/// }
///
////////////////////////////////////////////////////////////