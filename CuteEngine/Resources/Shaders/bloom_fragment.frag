#version 330 core

in Data
{
 vec2 UV_coords;
}FSIn;

uniform sampler2D blurred_texture;
uniform int mipmap_number;

out vec4 outColor;

void main(void)
{
	

	for(int i = 0; i < mipmap_number; i++)
	{
		outColor += textureLod(blurred_texture, FSIn.UV_coords , i);
	}


}
