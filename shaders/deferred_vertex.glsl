#version 400

/*
====================
Layouts
====================
*/
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

/*
====================
Uniform Variables
====================
*/
uniform mat4 u_mvp;
uniform mat4 u_model;

/*
====================
Out Variables
====================
*/
out VS_OUT
{
	vec3 world_position;
	vec3 world_normal;
	vec2 uv;
	
} vs_out;
	
/*
====================
Functions
====================
*/
void main()
{
	vs_out.world_position = (u_model * vec4(position, 1.0)).xyz;
	vs_out.world_normal   = transpose(inverse(mat3(u_model))) * normal;
	vs_out.uv		      = uv;
		
	gl_Position = u_mvp * vec4(position, 1.0);
}