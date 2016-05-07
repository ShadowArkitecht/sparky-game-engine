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

#ifndef __SPARKY_DIRECTIONAL_LIGHT_HPP__
#define __SPARKY_DIRECTIONAL_LIGHT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\lighting\light.hpp>	// Directional Light is a type of light class.

namespace sparky
{
	struct SPARKY_DIRECTIONAL_LIGHT_DESC
	{
		/*
		====================
		Member Variables
		====================
		*/
		SPARKY_BASE_LIGHT_DESC base;		// The base description of the Directional Light.
		Vector3f			   direction;	// Direction of the light.
	};

	class DirectionalLight final : public Light
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Vector3f m_direction;	// Direction that the Directional light will shine.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief The construction of the Directional Light with a description.
		///
		/// The description describes the parameters in which the directional
		/// light is created. 
		/// 
		/// \param desc		The description of the directional light.
		///
		////////////////////////////////////////////////////////////
		explicit DirectionalLight(const SPARKY_DIRECTIONAL_LIGHT_DESC& desc);

		////////////////////////////////////////////////////////////
		/// \brief Default destruction of the Directional Light object.
		////////////////////////////////////////////////////////////
		DirectionalLight(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the current direction of the Directional Light object.
		///
		/// The direction of the light controls which way that the light
		/// will shine in.
		///
		/// \retval Vector3f	The direction of the light.
		///
		////////////////////////////////////////////////////////////	
		const Vector3f& getDirection(void) const;

		////////////////////////////////////////////////////////////	
		/// \brief Sets a new direction for the Directional Light object.
		///
		/// The direction of the light controls which way that the light
		/// will shine in.
		/// 
		/// \param direction	The new direction of the Directional Light.
		///
		////////////////////////////////////////////////////////////
		void setDirection(const Vector3f& direction);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Sets the uniform variables of the Directional Light.
		///
		/// The directional lights are constructed within the shader as
		/// a struct. These uniforms comply with the variables of the structs.
		///
		/// \param uniform	The uniform class of the currently bound shader.
		///
		////////////////////////////////////////////////////////////
		void setUniforms(Uniform& uniform);
	};

}//namespace sparky

#endif//__SPARKY_DIRECTIONAL_LIGHT_HPP__