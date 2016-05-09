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

#ifndef __SPARKY_POINT_LIGHT_HPP__
#define __SPARKY_POINT_LIGHT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\lighting\light.hpp>	// Point light is a type of light.

namespace sparky
{
	struct Attenuation
	{
		/*
		====================
		Member Variables
		====================
		*/
		float constant;	///< The constant
		float linear;	///< The linearity.
		float exponent;	///< The quadratic exponent.
	};

	struct SPARKY_POINT_LIGHT_DESC
	{
		/*
		====================
		Member Variables
		====================
		*/
		SPARKY_BASE_LIGHT_DESC base;		///< The base parameters of the light.
		Attenuation			   attenuation;	///< "Fall-off" of the current light.
		float				   range;		///< Maximum range of effect.
	};

	class PointLight final : public Light
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		Attenuation m_attenuation; ///< "Fall-off" of the current light.
		float		m_range;	   ///< Maximum range of effect.

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructs a PointLight object from a description.
		///
		/// The description will define the behaviour of this PointLight.
		/// The members of the class will be set to those within the 
		/// description and applied within the shader.
		///
		/// \param desc		The description of the PointLight object.
		///
		////////////////////////////////////////////////////////////
		explicit PointLight(const SPARKY_POINT_LIGHT_DESC& desc);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the PointLight object.
		////////////////////////////////////////////////////////////
		~PointLight(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the attenuation of this PointLight.
		///
		/// The attenuation refers to the reduction or "fall-off" of 
		/// the light over a distance. 
		///
		/// \retval Attenuation		The Attenuation of the PointLight.
		///
		////////////////////////////////////////////////////////////
		const Attenuation& getAttenuation(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the attenuation of the PointLight.
		///
		/// The attenuation refers to the reduction or "fall-off" of 
		/// the light over a distance. 
		///
		/// \param attenuation	The new attenuation of the PointLight.
		///
		////////////////////////////////////////////////////////////
		void setAttenuation(const Attenuation& attenuation);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the range of the PointLight.
		///
		/// The range refers to the maximum radius of effect that this
		/// PointLight will have on any geometry within the scene.
		///
		/// \retval float	The range of the PointLight.
		///
		////////////////////////////////////////////////////////////
		float getRange(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the maximum radius of the PointLight.
		///
		/// The range refers to the maximum radius of effect that this
		/// PointLight will have on any geometry within the scene.
		///
		/// \param range	The new maximum range of the PointLight.
		///
		////////////////////////////////////////////////////////////
		void setRange(const float range);

		/*
		====================
		Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Sets the uniform variables of a PointLight within a shader.
		///
		/// Whenever a PointLight is used within a shader, the variables
		/// of the PointLight must be updated for correct shading behaviour.
		///
		/// \param uniform	The Uniforms of the currently bound shader.
		///
		////////////////////////////////////////////////////////////
		void setUniforms(Uniform& uniform);

		////////////////////////////////////////////////////////////
		/// \brief Adds the light to the current pipeline if the conditions
		///        are correct.
		///
		/// For Point Lights their position and radius is checked using the
		/// sphere check in the Frustum class. If they are currently within
		/// view, they are added to the GameManager for rendering this frame.
		///
		////////////////////////////////////////////////////////////
		void addLight(void) override;
	};

}//namespace sparky

#endif//__SPARKY_POINT_LIGHT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::PointLight
/// \ingroup lighting
///
/// sparky::PointLight is a light based component of the Sparky 
/// Engine. A PointLight can be used to represent a Light source
/// with a specific radius of effect, such as a lantern or torch on 
/// a wall. 
///
/// Similar to other lights within the application, it uses descriptions
/// to define it's behaviour. Below is a code example.
///
/// Usage example:
/// \code
/// // Create a description and "zero" it out.
/// sparky::SPARKY_POINT_LIGHT_DESC desc;
/// memset(&desc, 0, sizeof(sparky::SPARKY_POINT_LIGHT_DESC));
///
/// // Set the information of the description.
/// desc.base.name = "u_light";
/// desc.base.position = sparky::Vector3f::zero();
/// desc.base.colour = sparky::Vector3f(0.5f, 0.0f, 0.0f);
/// desc.base.intensity = 0.8f;
///
/// desc.attenuation.constant = 1.0f;
/// desc.attenuation.linear = 0.7f;
/// desc.attenuation.exponent = 1.8f;
///
/// desc.range = 15.0f;
///
/// // Create a light with the description and retain.
/// sparky::PointLight* pLight = new sparky::PointLight(desc);
/// pLight->addRef();
///
/// // Update the uniforms within a shader object.
/// pLight->setUniforms(m_uniform);
/// \endcode
///
////////////////////////////////////////////////////////////