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
#include <sparky\rendering\ishader.hpp>		// Class definition.
#include <sparky\rendering\GLSLobject.hpp>	// Individual GLSL shaders.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	IShaderComponent::IShaderComponent(void)
		: Ref(), m_program(), m_uniform(&m_program)
	{
	}

	////////////////////////////////////////////////////////////
	IShaderComponent::IShaderComponent(const String& vertexShader, const String& fragmentShader)
		: Ref(), m_program(), m_uniform(&m_program)
	{
		m_program.attachShader(new GLSLObject(vertexShader, eShaderType::VERTEX));
		m_program.attachShader(new GLSLObject(fragmentShader, eShaderType::FRAGMENT));

		m_program.link();
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	void IShaderComponent::bind(void) const
	{
		m_program.bind();
	}

	////////////////////////////////////////////////////////////
	void IShaderComponent::unbind(void) const
	{
		m_program.unbind();
	}

}//namespace sparky