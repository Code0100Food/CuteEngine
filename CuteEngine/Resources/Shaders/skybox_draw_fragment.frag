#version 330 core

in vec4 local_position;

uniform samplerCube Cubemap;
out vec4 out_color;

void main()
{
    	out_color = vec4(1.5);

	vec4 NDC = local_position / local_position.w;
	gl_FragDepth = NDC.z * 0.5 + 0.5;

	//vec3 color = vec3(); 
	//out_color = vec4(local_position.r, 0.0, 0.0, 1.0);
}
