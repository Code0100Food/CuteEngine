#version 330 core

layout(location=0) in vec3 position;


uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform vec3 camera_pos;

out vec3 local_position;

void main()
{
	local_position = position;
	gl_Position   = projection_matrix * view_matrix * vec4( camera_pos + position, 1.0);
	
}
