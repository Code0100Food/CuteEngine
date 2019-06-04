#version 330 core

layout(location=0) in vec3 position;


uniform mat4 projection_matrix;
uniform mat4 view_matrix;

uniform mat4 model_matrix;

uniform vec3 camera_pos;

out vec4 local_position;

void main()
{
	local_position = projection_matrix * view_matrix * model_matrix* vec4(position, 1.0);
	gl_Position = local_position;
	//pos = vec4(pos.xyz/pos.z, pos.w);
	//gl_Position = pos;
	
}
