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
	class DirectionalLight;

	class FinalShader final : public IShaderComponent
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Basic Shader object.
		///
		/// The Basic Shader inherits from the behaviour of the IShaderComponent
		/// object, loads and compiles the basic vertex and fragment
		/// shaders for use.
		///
		////////////////////////////////////////////////////////////
		explicit FinalShader(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Basic Shader object.
		////////////////////////////////////////////////////////////
		~FinalShader(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Updates the Uniform values of the Basic Shader.
		///
		/// The basic shader will convert the transform into a 
		/// model, view, projection matrix before passing the value to
		/// the shader. Update will also perform basic texture binding
		/// and the setting of lighting uniform variables.
		///
		/// \param transform	The transform of the current object being rendered.
		///
		////////////////////////////////////////////////////////////
		void update(const Transform& transform) override;
	};

}//namespace sparky

#endif//__SPARKY_BASIC_SHADER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::FinalShader
/// \ingroup rendering
///
/// sparky::FinalShader is a child class of the abstract 
/// IShaderComponent class. The basic shader only performs
/// basic shader functionality on an object, which is converting
/// the model to view co-ordinates, binding a texture and performing
/// some basic lighting.
///
/// sparky::FinalShader does not utilise the deferred rendering
/// pipeline and therefore is not optimised for use, and is used
/// more for testing purposes. Below is an example of use.
///
/// \code
/// // Get a shader from the resource manager.
/// sparky::FinalShader pShader = sparky::ResourceManager::getInstance().getShader<sparky::FinalShader>("basic");
///
/// // Create a transform.
/// sparky::Transform t;
/// t.setPosition(0.0f, 0.0f, 5.0f);
///
/// // Pass the transform to the shader.
/// pShader->update(t);
///
////////////////////////////////////////////////////////////