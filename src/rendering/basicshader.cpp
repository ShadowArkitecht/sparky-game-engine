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
#include <sparky\rendering\basicshader.hpp>	// Class definition.
#include <sparky\math\transform.hpp>		// Setting uniform variables.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	BasicShader::BasicShader(void)
		: IShaderComponent("shaders/basic_vertex.glsl", "shaders/basic_fragment.glsl")
	{
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void BasicShader::update(const Transform& transform) const
	{
		Matrix4f view = Matrix4f::translation(Vector3f(0.0f, 0.0f, 70.0f)) * Matrix4f::perspective(Vector3f::forward(), Vector3f::up());
		Matrix4f proj = Matrix4f::projection(45.0f, 640.0f / 480.0f, 1.0f, 1000.0f);

		Matrix4f mvp = transform.getTransformation() * view * proj;

		m_uniform.setParameter("u_mvp", mvp);
	}

}//namespace sparky