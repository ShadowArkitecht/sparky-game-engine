#version 400

/*
====================
Layouts
====================
*/
layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normal;
layout (location = 2) out vec3 g_diffuse;

/*
====================
Uniform Variables
====================
*/
uniform sampler2D u_texture;

/*
====================
In Variables
====================
*/
in VS_OUT
{
	vec3 world_position;
	vec3 world_normal;
	vec2 uv;
	
} fs_in;

/*
====================
Functions
====================
*/
void main()
{
	g_position = fs_in.world_position;
	g_normal   = normalize(fs_in.world_normal);
	
	g_diffuse  = texture(u_texture, fs_in.uv).rgb;
}