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

#ifndef __SPARKY_DEFERRED_SHADER_HPP__
#define __SPARKY_DEFERRED_SHADER_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\ishader.hpp>	// DeferredShader is a type of Shader component.

namespace sparky
{
	class DeferredShader final : public IShaderComponent
	{
	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor for the DeferredShader object.
		///
		/// The default constructor will call the IShaderComponent constructor
		/// and pass in the external deferred shaders for compilation and linking.
		///
		////////////////////////////////////////////////////////////
		explicit DeferredShader(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the DeferredShader object.
		////////////////////////////////////////////////////////////
		~DeferredShader(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Override Update method for the DeferredShader.
		///
		/// This update method will bake the information of each piece
		/// of geometry, it will bake the positional, diffuse and normal
		/// information as textures and output them for use with subsequent
		/// shaders.
		///
		/// \param transform	The Transform of the currently rendering object.
		///
		////////////////////////////////////////////////////////////
		void update(const Transform& transform) override;
	};

}//namespace sparky

#endif//__SPARKY_DEFERRED_SHADER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::DeferredShader
/// \ingroup rendering
/// 
/// sparky::DeferredShader is the most important shader utilised
/// within the application. It is responsible for outputting the
/// information baked into the GBuffer into a format that subsequent
/// shaders of the engine can utilise for additional shader. The class
/// can be combined with other shaders as long as they comply with the
/// deferred rendering pipeline.
///
/// Usage example:
/// \code
/// // Get a shader from the resource manager.
/// sparky::DeferredShader pShader = sparky::ResourceManager::getInstance().getShader<sparky::DeferredShader>("deferred");
///
/// // Create a transform.
/// sparky::Transform t;
/// t.setPosition(0.0f, 0.0f, 5.0f);
///
/// // Pass the transform to the shader.
/// pShader->update(t);
/// \endcode
///
////////////////////////////////////////////////////////////