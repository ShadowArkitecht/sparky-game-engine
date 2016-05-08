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
#include <sparky\lighting\pointlight.hpp>	// Class definition.
#include <sparky\rendering\uniform.hpp>		// Set the variables within the shader.
#include <sparky\math\frustum.hpp>			// Check if the point light is within the current frame.
#include <sparky\core\gamemanager.hpp>		// Add the current light to the game manager.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	PointLight::PointLight(const SPARKY_POINT_LIGHT_DESC& desc)
		: Light(desc.base), m_attenuation(desc.attenuation), m_range(desc.range)
	{
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	const Attenuation& PointLight::getAttenuation(void) const
	{
		return m_attenuation;
	}

	////////////////////////////////////////////////////////////
	void PointLight::setAttenuation(const Attenuation& attenuation)
	{
		m_attenuation = attenuation;
	}

	////////////////////////////////////////////////////////////
	float PointLight::getRange(void) const
	{
		return m_range;
	}

	////////////////////////////////////////////////////////////
	void PointLight::setRange(const float range)
	{
		m_range = range;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void PointLight::setUniforms(Uniform& uniform)
	{
		Light::setUniforms(uniform, ".base");

		uniform.setParameter(String::concat(this->getName(), ".attenuation.constant"), m_attenuation.constant);
		uniform.setParameter(String::concat(this->getName(), ".attenuation.linear"),   m_attenuation.linear);
		uniform.setParameter(String::concat(this->getName(), ".attenuation.exponent"), m_attenuation.exponent);

		uniform.setParameter(String::concat(this->getName(), ".range"), m_range);
	}

	////////////////////////////////////////////////////////////
	void PointLight::addLight(void)
	{
		if (Frustum::checkSphere(getPosition(), m_range))
		{
			GameManager::getInstance().addLight(this);
		}
	}

}//namespace sparky