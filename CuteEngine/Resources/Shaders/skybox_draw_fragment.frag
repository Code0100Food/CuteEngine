#version 330 core

in vec3 local_position;

uniform samplerCube Cubemap;
out vec4 out_color;

void main()
{
    	out_color = texture(Cubemap, local_position);
	//vec3 color = vec3(); 
	//out_color = vec4(local_position.r, 0.0, 0.0, 1.0);
}
