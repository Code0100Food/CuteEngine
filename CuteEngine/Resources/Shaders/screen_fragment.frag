#version 330 core

uniform sampler2D color_texture;

in Data
{
 vec2 UV_coords;
}FSIn;

out vec4 outColor;

void main(void)
{	

    float gamma_correction = 2.2;	
    outColor = texture(color_texture, FSIn.UV_coords);
    outColor.rgb = pow(outColor.rgb, vec3(1.0/gamma_correction));
}
