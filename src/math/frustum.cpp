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
Class Includes
====================
*/
#include <sparky\math\frustum.hpp>	// Class definition.
#include <sparky\core\camera.hpp>	// Frustum constructed from the Camera's viewport.

namespace sparky
{
	/*
	====================
	Static Fields
	====================
	*/
	std::array<FrustumPlane_t, 6> Frustum::m_planes;

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Frustum::construct(void)
	{
		float zMin, screenDiff;

		Matrix4f view = Camera::getMain().getView();
		Matrix4f proj = Camera::getMain().getProjection();

		Matrix4f vp;

		zMin = -proj.m[3][2] / proj.m[2][2];
		screenDiff = Camera::getMain().getFarPlane() / (Camera::getMain().getFarPlane() - zMin);

		proj.m[2][2] = screenDiff;
		proj.m[3][2] = -screenDiff * zMin;

		vp = view * proj;

		// Near Plane
		m_planes.at(0).position.x = vp.m[0][3] + vp.m[0][2];
		m_planes.at(0).position.y = vp.m[1][3] + vp.m[1][2];
		m_planes.at(0).position.z = vp.m[2][3] + vp.m[2][2];
		m_planes.at(0).distance   = vp.m[3][3] + vp.m[3][2];

		m_planes.at(0).normalize();

		// Far Plane
		m_planes.at(1).position.x = vp.m[0][3] - vp.m[0][2];
		m_planes.at(1).position.y = vp.m[1][3] - vp.m[1][2];
		m_planes.at(1).position.z = vp.m[2][3] - vp.m[2][2];
		m_planes.at(1).distance   = vp.m[3][3] - vp.m[3][2];

		m_planes.at(1).normalize();

		// Left Plane
		m_planes.at(2).position.x = vp.m[0][3] + vp.m[0][0];
		m_planes.at(2).position.y = vp.m[1][3] + vp.m[1][0];
		m_planes.at(2).position.z = vp.m[2][3] + vp.m[2][0];
		m_planes.at(2).distance   = vp.m[3][3] + vp.m[3][0];

		m_planes.at(2).normalize();

		// Right Plane
		m_planes.at(3).position.x = vp.m[0][3] - vp.m[0][0];
		m_planes.at(3).position.y = vp.m[1][3] - vp.m[1][0];
		m_planes.at(3).position.z = vp.m[2][3] - vp.m[2][0];
		m_planes.at(3).distance   = vp.m[3][3] - vp.m[3][0];

		m_planes.at(3).normalize();

		// Top Plane
		m_planes.at(4).position.x = vp.m[0][3] - vp.m[0][1];
		m_planes.at(4).position.y = vp.m[1][3] - vp.m[1][1];
		m_planes.at(4).position.z = vp.m[2][3] - vp.m[2][1];
		m_planes.at(4).distance   = vp.m[3][3] - vp.m[3][1];

		m_planes.at(4).normalize();

		// Bottom Plane
		m_planes.at(5).position.x = vp.m[0][3] + vp.m[0][1];
		m_planes.at(5).position.y = vp.m[1][3] + vp.m[1][1];
		m_planes.at(5).position.z = vp.m[2][3] + vp.m[2][1];
		m_planes.at(5).distance   = vp.m[3][3] + vp.m[3][1];

		m_planes.at(5).normalize();
	}

	////////////////////////////////////////////////////////////
	bool Frustum::checkPoint(const Vector3f& position)
	{
		for (const auto& plane : m_planes)
		{
			if (Vector3f::dot(position, plane.position) + plane.distance < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	bool Frustum::checkSphere(const Vector3f& position, const float radius)
	{
		for (const auto& plane : m_planes)
		{
			if (Vector3f::dot(position, plane.position) + plane.distance + radius < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	bool Frustum::checkCube(const Vector3f& position, const float size)
	{
		for (const auto& plane : m_planes)
		{
			if (Vector3f::dot(position, plane.position) + plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x + size, position.y, position.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x, position.y + size, position.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x + size, position.y + size, position.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x, position.y, position.z + size), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x + size, position.y, position.z + size), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x, position.y + size, position.z + size), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(position + size, plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			return false;
		}

		return true;
	}

	////////////////////////////////////////////////////////////
	bool Frustum::checkRectangle(const Vector3f& position, const Vector3f& size)
	{
		for (const auto& plane : m_planes)
		{
			if (Vector3f::dot(position, plane.position) + plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x + size.x, position.y, position.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x, position.y + size.y, position.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x + size.x, position.y + size.y, position.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x, position.y, position.z + size.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x + size.x, position.y, position.z + size.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(Vector3f(position.x, position.y + size.y, position.z + size.z), plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			if (Vector3f::dot(position + size, plane.position)
				+ plane.distance >= 0)
			{
				continue;
			}

			return false;
		}

		return true;
	}
}//namespace sparky