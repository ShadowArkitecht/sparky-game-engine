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
#include <sparky\core\camera.hpp>	// Class definition.
#include <sparky\utils\config.hpp>	// Parsing variables from a configuration file.
#include <sparky\core\window.hpp>	// Loading the variables from a Window object.

namespace sparky
{
	/*
	====================
	Static Fields
	====================
	*/
	////////////////////////////////////////////////////////////
	Camera* Camera::m_pMain = nullptr;

	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Camera::Camera(void)
		: m_transform(), m_fov(0.0f), m_dimensions(), m_nearPlane(0.0f), m_farPlane(0.0f)
	{
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	Camera& Camera::getMain(void)
	{
		return *m_pMain;
	}

	////////////////////////////////////////////////////////////
	void Camera::setMain(Camera& camera)
	{
		m_pMain = &camera;
	}

	////////////////////////////////////////////////////////////
	Transform& Camera::getTransform(void)
	{
		return m_transform;
	}

	////////////////////////////////////////////////////////////
	float Camera::getFoV(void) const
	{
		return m_fov;
	}

	////////////////////////////////////////////////////////////
	void Camera::setFoV(const float fov)
	{
		m_fov = fov;
	}

	////////////////////////////////////////////////////////////
	const Vector2f& Camera::getDimensions(void) const
	{
		return m_dimensions;
	}

	////////////////////////////////////////////////////////////
	void Camera::setDimensions(const Vector2f& dimensions)
	{
		m_dimensions = dimensions;
	}

	////////////////////////////////////////////////////////////
	float Camera::getNearPlane(void) const
	{
		return m_nearPlane;
	}

	////////////////////////////////////////////////////////////
	void Camera::setNearPlane(const float plane)
	{
		m_nearPlane = plane;
	}

	////////////////////////////////////////////////////////////
	float Camera::getFarPlane(void) const
	{
		return m_farPlane;
	}

	////////////////////////////////////////////////////////////
	void Camera::setFarPlane(const float plane)
	{
		m_farPlane = plane;
	}

	////////////////////////////////////////////////////////////
	Matrix4f Camera::getProjection(void) const
	{
		return Matrix4f::projection(m_fov, m_dimensions.x / m_dimensions.y, m_nearPlane, m_farPlane);
	}

	////////////////////////////////////////////////////////////
	Matrix4f Camera::getView(void) const
	{
		return Matrix4f::translation(-m_transform.getPosition()) * Matrix4f::perspective(m_transform.forward(), m_transform.up());
	}

	////////////////////////////////////////////////////////////
	Matrix4f Camera::getViewProjection(void) const
	{
		return getView() * getProjection();
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Camera::create(void)
	{
		ConfigFile file;
		file.open("data/config.hycfg");

		this->create(file);
	}

	////////////////////////////////////////////////////////////
	void Camera::create(const ConfigFile& config)
	{
		Vector2f dim(config.getFloat("Camera.dimension_x"), config.getFloat("Camera.dimension_y"));
		this->create(config.getFloat("Camera.field_of_view"), dim, config.getFloat("Camera.near_clipping_plane"), config.getFloat("Camera.far_clipping_plane"));
	}

	////////////////////////////////////////////////////////////
	void Camera::create(const Window& window)
	{
		this->create(70.0f, Vector2f(window.getSize()), 0.1f, 1000.0f);
	}

	////////////////////////////////////////////////////////////
	void Camera::create(const float fov, const Vector2f& dimensions, const float nearClippingPlane, const float farClippingPlane)
	{
		m_fov = fov;
		m_dimensions = dimensions;
		m_nearPlane = nearClippingPlane;
		m_farPlane = farClippingPlane;

		if (!m_pMain)
		{
			m_pMain = this;
		}
	}

}//namespace sparky