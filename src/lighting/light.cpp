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
#include <sparky\lighting\light.hpp>	// Class definition.
#include <sparky\rendering\uniform.hpp>	// Sending light information to the shader.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	Light::Light(const SPARKY_BASE_LIGHT_DESC& desc)
		: Ref(), m_name(desc.name), m_position(desc.position), m_colour(desc.colour), m_intensity(desc.intensity)
	{
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	const String& Light::getName(void) const
	{
		return m_name;
	}

	////////////////////////////////////////////////////////////
	void Light::setName(const String& name)
	{
		m_name = name;
	}

	////////////////////////////////////////////////////////////
	const Vector3f& Light::getPosition(void) const
	{
		return m_position;
	}

	////////////////////////////////////////////////////////////
	void Light::setPosition(const Vector3f& position)
	{
		m_position = position;
	}

	////////////////////////////////////////////////////////////
	const Vector3f& Light::getColour(void) const
	{
		return m_colour;
	}

	////////////////////////////////////////////////////////////
	void Light::setColour(const Vector3f& colour)
	{
		m_colour = colour;
	}

	////////////////////////////////////////////////////////////
	float Light::getIntensity(void) const
	{
		return m_intensity;
	}

	////////////////////////////////////////////////////////////
	void Light::setIntensity(const float intensity)
	{
		m_intensity = intensity;
	}

	/*
	====================
	Protected Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void Light::setUniforms(Uniform& uniform, const String& extension)
	{
		uniform.setParameter(String::concat(m_name, extension, ".position"), m_position);
		uniform.setParameter(String::concat(m_name, extension, ".colour"), m_colour);
		uniform.setParameter(String::concat(m_name, extension, ".intensity"), m_intensity);
	}

}//namespace sparky