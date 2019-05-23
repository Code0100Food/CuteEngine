#version 330 core

in Data
{
 vec3 normal;
 vec2 uv_coords;

}FSIn;

uniform sampler2D albedo_texture;
uniform bool is_selected;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out vec4 outSelection;

void main(void)
{
    outColor = texture(albedo_texture, FSIn.uv_coords);
    outNormal = vec4(FSIn.normal,1.0);

    if(is_selected)
	outSelection = vec4(1.0);
    else outSelection = vec4(0.0);
}
