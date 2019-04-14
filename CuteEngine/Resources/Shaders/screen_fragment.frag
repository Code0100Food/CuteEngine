#version 330 core

uniform sampler2D color_texture;

in Data
{
 vec2 UV_coords;
}FSIn;

out vec4 outColor;

void main(void)
{
	vec3 lol = texture(color_texture, FSIn.UV_coords).rgb;
    outColor = texture(color_texture, FSIn.UV_coords); //vec4(FSIn.UV_coords.x, FSIn.UV_coords.y, 0.0, 1.0);//texture(color_texture, FSIn.UV_coords);
}
