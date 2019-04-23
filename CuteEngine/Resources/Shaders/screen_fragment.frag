#version 330 core

uniform sampler2D color_texture;

in Data
{
 vec2 UV_coords;
}FSIn;

out vec4 outColor;

void main(void)
{
	
    outColor = texture(color_texture, FSIn.UV_coords);
}
