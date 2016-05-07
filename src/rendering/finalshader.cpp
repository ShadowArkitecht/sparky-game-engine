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
#include <sparky\rendering\finalshader.hpp>	    // Class definition.
#include <sparky\lighting\directionallight.hpp> // Directional Light Test.
#include <sparky\lighting\pointlight.hpp>		// Point Light Test.
#include <sparky\math\transform.hpp>		    // Setting uniform variables.
#include <sparky\core\camera.hpp>			    // Needed for view and projection matrices.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	FinalShader::FinalShader(void)
		: IShaderComponent("shaders/basic_vertex.glsl", "shaders/basic_fragment.glsl")
	{
		SPARKY_DIRECTIONAL_LIGHT_DESC desc;
		memset(&desc, 0, sizeof(SPARKY_DIRECTIONAL_LIGHT_DESC));

		desc.base.name = String("u_light");
		desc.base.position = Vector3f::one();
		desc.base.colour = Vector3f::one();
		desc.base.intensity = 0.5f;

		desc.direction = Vector3f(1.0f, 0.0f, 0.0f);

		m_pLight = new DirectionalLight(desc);
		m_pLight->addRef();


		SPARKY_POINT_LIGHT_DESC p;
		memset(&p, 0, sizeof(SPARKY_POINT_LIGHT_DESC));

		p.base.name = String("u_point_light");
		p.base.position = Vector3f(1.0f, 1.0f, 0.0f);
		p.base.colour = Vector3f(0.5f, 0.0f, 0.0f);
		p.base.intensity = 8.0f;

		p.attenuation.constant = 1.0f;
		p.attenuation.linear = 0.7f;
		p.attenuation.exponent = 1.8f;

		p.range = 25.0f;

		m_pPoint = new PointLight(p);
		m_pPoint->addRef();
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void FinalShader::update(const Transform& transform)
	{
		// Fragment uniforms.
		m_uniform.setParameter("u_position", 0);
		m_uniform.setParameter("u_normal",   1);
		m_uniform.setParameter("u_diffuse",  2);

		m_pLight->setUniforms(m_uniform);
		m_pPoint->setUniforms(m_uniform);
	}

}//namespace sparky