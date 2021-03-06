#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec2 UVcoords;


out Data
{
        vec2 UV_coords;
}VSOut;

void main(void)
{
        gl_Position = vec4(position, 1);
	VSOut.UV_coords = UVcoords;
}
