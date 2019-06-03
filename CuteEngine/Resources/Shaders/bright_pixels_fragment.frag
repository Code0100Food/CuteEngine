#version 330 core

in Data
{
 vec2 uv_coords;

}FSIn;

uniform sampler2D get_bright_pixels_texture;

void main(void)
{
	vec4 color = texture(get_bright_pixels_texture, FSIn.uv_coords); 

	if(color.r >= 1.0 || color.g >= 1.0 || color.b >= 1.0)
		outColor = color;
	else outColor = vec4(0.0);
}
