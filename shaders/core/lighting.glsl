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

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
	Light       base;
	Attenuation attenuation;
	float 		range;
};

////////////////////////////////////////////////////////////
/// \name 	sparky_CalculateLight
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
	float saturation = dot(world_normal, -direction);
	
	vec4 colour = vec4(0.0);

	if (saturation > 0.0)
	{
		colour = vec4(light.colour.xyz, 1.0) * light.intensity * saturation;
	}

	return colour;
}

////////////////////////////////////////////////////////////
/// \name 	sparky_CalculateDirectionalLight
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

////////////////////////////////////////////////////////////
/// \name 	sparky_CalculatePointLight
/// \brief 	Calculates the effect that a point light object will have on a particular fragment.
/// 
/// The calculation of the point light effect on a fragment will take in a point light object, the world position of the object and the world normals.
/// It will calculate the difference and length between the world position and the point light's position. If the distance is greater than the range
/// of the point light, the light will have no effect on the fragment. If the distance is less than the range, the colour is initially calculated with
/// hydra_CalculateLight and the attenuation of the light is calculated using the point light's attenuation member variable. The return colour is effected
/// by the calculated attenuation factor.
/// 
/// \param point_light		The point light to be calculated.
/// \param world_position   The position of the object (in world co-ordinates).
/// \param world_normal		The normals of the object (in world co-ordinates).
/// 
/// \retval colour				The current colour of the fragment after point light calculations.
///
////////////////////////////////////////////////////////////
vec4 sparky_CalculatePointLight(PointLight point_light, vec3 world_position, vec3 world_normal)
{
	// Calculate the direction that the light is currently facing.
	vec3 light_direction = world_position - point_light.base.position;
	// Calculate the length of the direction.
	float distance_to_point = length(light_direction);
	
	// If the length of the vector is greater than the range of the light, the current pixel will not be effected.
	if (distance_to_point > point_light.range)
	{
		return vec4(0.0);
	}
	
	light_direction = normalize(light_direction);
	// Calculate the base effect that the Light will have on the current pixel.
	vec4 colour = sparky_CalculateLight(point_light.base, light_direction, world_normal);
	// Calculate the "fall-off" of the current Point Light.
	float attenuation = point_light.attenuation.constant + 
						point_light.attenuation.linear * distance_to_point + 
						point_light.attenuation.exponent * distance_to_point * distance_to_point;
						
	// Returns the pixel colour, which is altered by the fall-off of the Attenuation.
	return colour / attenuation;
}

#endif//__SPARKY_LIGHTING_GLSL__