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

#ifndef __SPARKY_AMBIENT_SHADER_HPP__
#define __SPAKRY_AMBIENT_SHADER_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\ishader.hpp>	// Ambient Shader is a type of Shader object.

namespace sparky
{
	class AmbientShader final : public IShaderComponent
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the Ambient Shader object.
		///
		/// The default constructor will load the two external ambient
		/// shaders and compile them for use.
		///
		////////////////////////////////////////////////////////////
		explicit AmbientShader(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the Ambient Shader object.
		////////////////////////////////////////////////////////////
		~AmbientShader(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Update the information and uniforms of the shader object.
		///
		/// The ambient shader will only bind and update a single value,
		/// the ambient value of every object within the current scene.
		///
		////////////////////////////////////////////////////////////
		void update(const Transform& transform) override;
	};

}//namespace sparky

#endif//__SPARKY_AMBIENT_SHADER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::AmbientShader
/// \ingroup rendering
///
/// sparky::AmbientShader is an extremely basic shader object
/// that only binds and updates a single value within it's texture,
/// the global ambience of every object within the scene. This shader
/// is bound and used before all of the lighting calculations.
///
////////////////////////////////////////////////////////////