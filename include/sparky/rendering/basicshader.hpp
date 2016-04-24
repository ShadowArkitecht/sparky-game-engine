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

#ifndef __SPARKY_BASIC_SHADER_HPP__
#define __SPARKY_BASIC_SHADER_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\ishader.hpp>	// Basic Shader is a type of shader.

namespace sparky
{
	class BasicShader final : public IShaderComponent
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		explicit BasicShader(void);
		~BasicShader(void) = default;

		/*
		====================
		Methods
		====================
		*/
		void update(const Transform& transform) const override;
	};

}//namespace sparky

#endif//__SPARKY_BASIC_SHADER_HPP__