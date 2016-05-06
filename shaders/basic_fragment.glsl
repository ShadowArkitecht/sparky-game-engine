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

#version 400

/*
====================
Uniform Variables
====================
*/
uniform sampler2D u_position;
uniform sampler2D u_diffuse;
uniform sampler2D u_normal;

/*
====================
In Variables
====================
*/
in VS_OUT
{
	vec2 uv_coords;
	
} fs_in;

/*
====================
Out Variables
====================
*/
out vec4 o_fragColour;

/*
====================
Functions
====================
*/
void main()
{
	vec3 frag_position  = texture(u_position, fs_in.uv_coords).rgb;
	vec3 frag_diffuse   = texture(u_diffuse,  fs_in.uv_coords).rgb;
	vec3 frag_normal    = texture(u_normal,   fs_in.uv_coords).rgb;

	o_fragColour = vec4(frag_diffuse, 1.0);
}