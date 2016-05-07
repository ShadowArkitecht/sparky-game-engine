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

#ifndef __SPARKY_LIGHT_HPP__
#define __SPARKY_LIGHT_HPP__

/*
====================
Class Includes
====================
*/
#include <sparky\core\ref.hpp>		// Light is a dynamically allocated object.
#include <sparky\utils\string.hpp>	// The name is stored as a sparky::String.
#include <sparky\math\vector3.hpp>	// The position and colour are Vector3 values.

namespace sparky
{
	/*
	====================
	Sparky Forward Declarations
	====================
	*/
	class Uniform;

	struct SPARKY_BASE_LIGHT_DESC
	{
		/*
		====================
		Member Variables
		====================
		*/
		String	 name;		// The name of the Light.
		Vector3f position;  // The position of the Light within the scene.
		Vector3f colour;	// RGB values of the light.
		float    intensity;	// The light intensity.
	};

	class Light : public Ref
	{
	private:
		/*
		====================
		Member Variables
		====================
		*/
		String   m_name;		// The name of the light (within the shader).
		Vector3f m_position;	// Position of the light within the scene.
		Vector3f m_colour;		// RGB values of the light.
		float    m_intensity;	// The light intensity.

	protected:
		/*
		====================
		Protected Methods
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Sets the uniforms of this Light object.
		///
		/// The uniforms are set so that the communication between this
		/// Light and the currently bound shader can be achieved.
		///
		/// \param uniform	A reference to the current Uniform object of the shader.
		///
		////////////////////////////////////////////////////////////
		void setUniforms(Uniform& uniform, const String& extension);

	public:
		/*
		====================
		Ctor and Dtor
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Constructor for the Light object with the parameters
		///        set to a description.
		///
		/// This constructor will utilise the values from the light description
		/// and set the member values accordingly. Descriptions are used as the
		/// lights have several variables to be set within the class itself.
		///
		/// \param desc		The description of the light.
		///
		////////////////////////////////////////////////////////////
		explicit Light(const SPARKY_BASE_LIGHT_DESC& desc);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor of the Light object.
		////////////////////////////////////////////////////////////
		virtual ~Light(void) = default;

		/*
		====================
		Getters and Setters
		====================
		*/
		////////////////////////////////////////////////////////////
		/// \brief Retrieves the name of the Light object.
		///
		/// The name refers to the name of the Light object within the
		/// corresponding shader.
		///
		/// \retval String	The name of the Light object.
		///
		////////////////////////////////////////////////////////////
		const String& getName(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the name of the Light object.
		///
		/// \param name		The name to set the Light object to.
		///
		////////////////////////////////////////////////////////////
		void setName(const String& name);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the position of the Light object.
		///
		/// The position refers to the co-ordinates of the light within
		/// 3D space.
		///
		/// \retval Vector3f	The position of the Light object.
		///
		////////////////////////////////////////////////////////////
		const Vector3f& getPosition(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Set the position of the Light object within the scene.
		///
		/// The position refers to the co-ordinates of the light within
		/// 3D space.
		///
		/// \param position	The new position of the Light object.
		///
		////////////////////////////////////////////////////////////
		void setPosition(const Vector3f& position);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the current colour of the Light object.
		///
		/// The colour of the Light refers to the RGB effect that this
		/// Light will have on nearby objects.
		///
		/// \retval Vector3f	The colour of the Light object.
		///
		////////////////////////////////////////////////////////////
		const Vector3f& getColour(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the new colour of the Light object.
		///
		/// The colour of the Light refers to the RGB effect that this
		/// Light will have on nearby objects.
		///
		/// \param colour	The new colour of the Light object.
		///
		////////////////////////////////////////////////////////////
		void setColour(const Vector3f& colour);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the intensity of the Light object.
		///
		/// The intensity is how strong the light shines on an object, the
		/// higher the value, the more intense the light.
		///
		/// \retval int		The intensity of the Light.
		///
		////////////////////////////////////////////////////////////
		float getIntensity(void) const;

		////////////////////////////////////////////////////////////
		/// \brief Sets the new intensity of the Light.
		///
		/// The intensity is how strong the light shines on an object, the
		/// higher the value, the more intense the light.
		///
		/// \param intensity	The new intensity of the Light.
		///
		////////////////////////////////////////////////////////////
		void setIntensity(const float intensity);
	};

}//namespace sparky

#endif//__SPARYK_LIGHT_HPP__

////////////////////////////////////////////////////////////
/// \class sparky::Light
/// \ingroup lighting
///
/// sparky::Light is the base parent class for all types of lighting
/// within the Sparky Engine. It controls the position and overall
/// colour of the light within the scene. The light itself cannot be
/// used and can only be utilised through it's child classes. A
/// code example is provided in sparky::PointLight and 
/// sparky::DirectionalLight.
///
////////////////////////////////////////////////////////////