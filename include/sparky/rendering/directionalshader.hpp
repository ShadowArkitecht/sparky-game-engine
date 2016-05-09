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
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class DirectionalLight;

	class DirectionalShader final : public IShaderComponent
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		DirectionalLight* m_pLight;	///< The directional light of the shader.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default construction of the Directional Shader object.
		///
		/// The Directional Shader inherits from the behaviour of the IShaderComponent
		/// object, loads and compiles the basic vertex and fragment
		/// shaders for use.
		///
		////////////////////////////////////////////////////////////
		explicit DirectionalShader(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Directional Shader object.
		////////////////////////////////////////////////////////////
		~DirectionalShader(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Sets the directional light to render with the current
		///        shader object.
		///
		/// \param pLight	The directional light of the shader.
		///
		////////////////////////////////////////////////////////////
		void setActiveLight(DirectionalLight* pLight);

		////////////////////////////////////////////////////////////
		/// \brief Updates the Uniform values of the Basic Shader.
		///
		/// The directional shader will bind the textures generated by
		/// the deferred pipeline and apply a directional light effect to
		/// the objects.
		///
		/// \param transform	The transform of the current object being rendered.
		///
		////////////////////////////////////////////////////////////
		void update(const Transform& transform) override;
	};

}//namespace sparky

#endif//__SPARKY_BASIC_SHADER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::DirectionalShader
/// \ingroup rendering
///
/// sparky::DirectionalShader is one of the lighting specific shaders
/// used within the application. It is responsible for calculation the
/// effect that a directional light will have on the geometry within a 
/// scene. It is used in conjunction with the PointShader for multi-pass
/// lighting.
///
/// Usage example:
/// \code
/// // Get a shader from the resource manager.
/// sparky::DirectionalShader pShader = sparky::ResourceManager::getInstance().getShader<sparky::DirectionalShader>("direction");
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