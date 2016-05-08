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

#ifndef __SPARKY_POINT_SHADER_HPP__
#define __SPARKY_POINT_SHADER_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\rendering\ishader.hpp>	// Point Shader is a type of IShaderComponent object.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class PointLight;

	class PointShader final : public IShaderComponent
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		PointLight* m_pLight;	// The currently active point light.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Default constructor of the PointShader object. 
		///
		/// The default constructor will bind and compile the two external
		/// shaders for use with Point Lights. This shader is used within 
		/// the multi-pass rendering pipeline to render point lights onto
		/// geometry.
		///
		////////////////////////////////////////////////////////////
		explicit PointShader(void);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the Point Shader object.
		////////////////////////////////////////////////////////////
		~PointShader(void) = default;

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Sets the currently active point light of the multi-pass
		///        rendering pipeline.
		///
		/// \param pLight	The currently active point light.
		///
		////////////////////////////////////////////////////////////
		void setActiveLight(PointLight* pLight);

		////////////////////////////////////////////////////////////
		/// \brief Updates the uniforms of the point light shader.
		///
		/// The uniforms updated within this shader is the currently
		/// active point light and the normals generated from the 
		/// deferred rendering pipeline.
		///
		/// \param transform	The transform of the currently rendering object.
		///
		////////////////////////////////////////////////////////////
		void update(const Transform& transform) override;
	};

}//namespace sparky

#endif//__SPARKY_POINT_SHADER_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::PointShader
/// \ingroup rendering
///
/// sparky::PointShader is one of the shaders used within the 
/// applications multi-pass rendering pipeline. It is responsible
/// for rendering the effects of point lights onto geometry.
///
/// sparky::PointShader never has to be used implicitly by the
/// user, instead it is utilised to render the lights of the scene
/// within the game manager singleton class.
///
////////////////////////////////////////////////////////////