#version 330 core

in Data
{
 vec3 color;
 vec2 uv_coords;
}FSIn;

uniform sampler2D albedo_texture;
out vec4 outColor;

void main(void)
{
    outColor = texture(albedo_texture, FSIn.uv_coords);//vec4(FSIn.color,1.0);
}
