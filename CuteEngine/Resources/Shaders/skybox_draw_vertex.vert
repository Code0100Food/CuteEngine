#version 330 core

layout(location=0) in vec3 position;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 camera_pos_matrix;

out vec3 local_position;

void main()
{
	local_position = position;
	gl_Position   = projection_matrix * view_matrix * camera_pos_matrix * vec4(position, 1.0);
	
}
