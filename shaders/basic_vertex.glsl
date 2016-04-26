#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 u_mvp;

out VS_OUT
{
	vec2 uv;
	
} vs_out;
	
void main()
{
	vs_out.uv = uv;
	gl_Position = u_mvp * vec4(position, 1.0);
}