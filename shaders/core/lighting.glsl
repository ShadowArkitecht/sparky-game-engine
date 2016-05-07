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

#ifndef __SPARKY_LIGHTING_GLSL__
#define __SPARKY_LIGHTING_GLSL__

struct Light
{
	vec3  position;
	vec3  colour;
	float intensity;
};

struct DirectionalLight
{
	Light base;
	vec3  direction;
};

////////////////////////////////////////////////////////////
/// \name 	hydra_CalculateLight
/// \brief 	Calculates the effect that the parent base light of each light object will have on a particular fragment.
/// 
/// This function will calculate the effect that the light parameter will have on each individual fragment of the currently rendering
/// object. It calculates the attenuation of the light by calculating cosine angle between the world normal and the negative direction.
/// If the attenuation is greater than zero (not directly facing away from the camera) then the fragment will be effected by the lights
/// colour, its' intensity and the attenuation factor.
/// 
/// \param light			The light to retrieve the information of position, colour and intensity.
/// \param direction		The direction that the light is currently facing.
/// \param world_normal		The world normals of the object to be calculated.
/// 
/// \retval colour			The current colour of the fragment after lighting calculations.
///
////////////////////////////////////////////////////////////
vec4 sparky_CalculateLight(Light light, vec3 direction, vec3 world_normal)
{
	// this calculates the cosine angle between the inverse direction and the current normal
	// basically the direction towards the camera/eye
	float saturation = dot(world_normal, -direction);
	
	vec4 colour = vec4(0.0);
	// if the light is having any sort of effect on the current normal, then light will be calculated, else it will return [ 0, 0, 0, 0 ]
	if (saturation > 0.0)
	{
		colour = vec4(light.colour.xyz, 1.0) * light.intensity * saturation;
	}

	return colour;
}

////////////////////////////////////////////////////////////
/// \name 	hydra_CalculateDirectionalLight
/// \brief 	Calculates the effect that a directional light object will have on a particular fragment.
/// 
/// The calculation of the directional light will make use of a directional light object and the world normals of the object currently
/// being rendered. It calculate the effect by using the hydra_CalculateLight function and passes in the parent of the directional light,
/// it's current facing direction and the world normals. hydra_CalculateLight will calculate the attenuation and effect that the directional
/// light will have on each individual fragment of the currently rendering object.
/// 
/// \param dir_light		The directional light to be calculated.
/// \param world_normal		The world normals of the object to be calculated.
/// 
/// \retval colour			The current colour of the fragment after directional lighting calculations.
///
////////////////////////////////////////////////////////////
vec4 sparky_CalculateDirectionalLight(DirectionalLight dir_light, vec3 world_normal)
{
	return sparky_CalculateLight(dir_light.base, -dir_light.direction, world_normal);
}

#endif//__SPARKY_LIGHTING_GLSL__