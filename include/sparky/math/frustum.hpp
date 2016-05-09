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

#ifndef __SPARKY_FRUSTUM_HPP__
#define __SPARKY_FRUSTUM_HPP__

/*
====================
CPP Includes
====================
*/
#include <array>					// Stores all of the planes in the Frustum.
#include <sparky\math\vector3.hpp>	// Used for checking points and position in the Frustum.

namespace sparky
{
	struct FrustumPlane_t
	{
	public:
		/*
		====================
		Member Variables
		====================
		*/
		Vector3f position;	///< The position of the Plane.
		float    distance;	///< The distance of the Plane from the origin.
							
	public:
		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Normalizes the position and distance of the Frustum
		///		   planes.
		////////////////////////////////////////////////////////////
		void normalize(void)
		{
			float normal = position.magnitude();
			position /= normal;
			distance /= normal;
		}
	};

	class Frustum final
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		static std::array<FrustumPlane_t, 6> m_planes;	/// The planes of the Frustum.

	public:
		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs the view-port of the Frustum object.
		///
		/// This method is called every frame within the GameManager 
		/// singleton class and constructs the Frustum of the current
		/// viewport by reading the information provided by the Engine's 
		/// current main Camera. 
		///
		////////////////////////////////////////////////////////////
		static void construct(void);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see whether the specified point in 3D space
		///        is within the viewport of the Frustum.
		///
		/// \param point	The point to check.
		///
		/// \retval bool	True if the point parameter is inside the Frustum.
		///
		////////////////////////////////////////////////////////////
		static bool checkPoint(const Vector3f& point);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see whether the specified point and its radius
		///        is within the viewport of the Frustum.
		///
		/// \param position		The position to check.
		/// \param radius		The radius of the sphere.
		///
		/// \retval bool		True if the point parameter is inside the Frustum.
		///
		////////////////////////////////////////////////////////////
		static bool checkSphere(const Vector3f& position, const float radius);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see if the cube is within the Frustum object.
		///
		/// This method Checks to see if a cube shape is within the viewport of the
		/// Frustum. If any of the cubes points are within the Frustum, it will return
		/// true.
		///
		/// \param position		The anchor point of the cube.
		/// \param size			The uniform dimensions of the cube.
		///
		////////////////////////////////////////////////////////////
		static bool checkCube(const Vector3f& position, const float size);

		////////////////////////////////////////////////////////////
		/// \brief Checks to see if the rectangle shape is within the Frustum object.
		///
		/// This method Checks to see if a rectangle shape is within the viewport of the
		/// Frustum. If any of the rectangle points are within the Frustum, it will return
		/// true.
		///
		/// \param position		The anchor point of the rectangle.
		/// \param size			The x, y and z scale of the rectangle.
		///
		////////////////////////////////////////////////////////////
		static bool checkRectangle(const Vector3f& position, const Vector3f& size);
	};

}//namespace sparky

#endif//__SPARKY_FRUSTUM_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Frustum
/// \ingroup math
///
/// sparky::Frustum is an mathematical optimisation technique
/// used to check if objects of specific types (such as cubes or
/// spheres) is within the Camera's view-port. If these objects
/// are not within the view-port, there is no point spending the
/// GPU time renderin objects that cannot be seen.
///
/// The dimensions and direction of the Frustum are constructed
/// each frame within the GameManager singleton. Below is a code
/// checking if a point is within the Frustum.
///
/// Usage example:
/// \code
/// // Create a random point.
/// Vector3f point(5.0f, 50.0f, 10.0f);
///
/// // Test if it's in the Frustum, the result will depend on the
/// // direction and position of the current main camera.
/// if (Frustum::checkPoint(point))
/// {
///		std::cout << "Point is in Frustum!" << std::endl;
/// }
/// else
/// {
///		std::cout << "Point is outside Frustum!" << std::endl;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////