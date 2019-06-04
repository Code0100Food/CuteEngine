#version 330 core

in vec3 local_position;

uniform samplerCube cubemap;
out vec4 out_color;

void main()
{
    //out_color = texture(cubemap, local_position);
	vec3 color = vec3(local_position); 
	out_color = vec4(color.rgb, 1.0);
}
