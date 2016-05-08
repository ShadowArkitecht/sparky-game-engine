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
#include <sparky\math\transform.hpp>		    // Setting uniform variables.
#include <sparky\core\camera.hpp>			    // Needed for view and projection matrices.
#include <sparky\core\gamemanager.hpp>			// Get the currently active lights.
#include <sparky\lighting\directionallight.hpp> // Update the uniforms of the light.

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

		GameManager::getInstance().getActiveDirectional()->setUniforms(m_uniform);
	}

}//namespace sparky