#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

out Data
{
        vec3 color;
}VSOut;

void main(void)
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1);
        //gl_Position = vec4(position, 1);
        VSOut.color = color;
}
