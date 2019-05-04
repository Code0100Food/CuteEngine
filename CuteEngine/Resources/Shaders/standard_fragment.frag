#version 330 core

in Data
{
 vec3 normal;
 vec2 uv_coords;

}FSIn;

uniform sampler2D albedo_texture;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outNormal;

void main(void)
{
    outColor = texture(albedo_texture, FSIn.uv_coords);
    outNormal = vec4(FSIn.normal,1.0);
}
