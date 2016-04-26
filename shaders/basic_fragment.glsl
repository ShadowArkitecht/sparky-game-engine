#version 400

uniform sampler2D u_texture;

in VS_OUT
{
	vec2 uv;
	
} fs_in;

out vec4 o_frag_colour;

void main()
{
	o_frag_colour = texture2D(u_texture, fs_in.uv) * vec4(1.0);
}