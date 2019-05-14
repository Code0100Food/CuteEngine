#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec2 UVcoords;

out vec2 texCoord;

void main(void)
{
        texCoord = UVcoords;//position.xy * 0.5 + vec2(0.5);
        gl_Position = vec4(position, 1.0);
}
