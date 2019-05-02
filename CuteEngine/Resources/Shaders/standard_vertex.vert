#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 UVcoords;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

out Data
{
        vec3 color;
	vec2 uv_coords;
}VSOut;

void main(void)
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1);
	VSOut.uv_coords = UVcoords;
        VSOut.color = color;
}
