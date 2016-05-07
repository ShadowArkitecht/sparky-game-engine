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
#include <sparky\lighting\directionallight.hpp>	// Class definition.
#include <sparky\rendering\uniform.hpp>			// Sending variables to the shader.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	DirectionalLight::DirectionalLight(const SPARKY_DIRECTIONAL_LIGHT_DESC& desc)
		: Light(desc.base), m_direction(desc.direction)
	{
	}

	/*
	====================
	Getters and Setters
	====================
	*/
	////////////////////////////////////////////////////////////
	const Vector3f& DirectionalLight::getDirection(void) const
	{
		return m_direction;
	}

	////////////////////////////////////////////////////////////
	void DirectionalLight::setDirection(const Vector3f& direction)
	{
		m_direction = direction;
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void DirectionalLight::setUniforms(Uniform& uniform)
	{
		Light::setUniforms(uniform, ".base");

		uniform.setParameter(String::concat(this->getName(), ".direction"), m_direction);
	}

}//namespace sparky