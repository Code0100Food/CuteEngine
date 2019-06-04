#version 330 core

in vec3 local_position;


uniform sampler2D equirectangular_map;

out vec4 out_color;

const vec2 inv_atan = vec2(0.1591, 0.3183); // (1/2pi, 1/pi)

vec2 SampleSphericalMap(vec3 aVec)
{
    vec2 uv = vec2(atan(aVec.z, aVec.x), asin(aVec.y));
    uv *= inv_atan;
    uv += 0.5;
    return uv;
}

void main()
{
    vec2 uv = SampleSphericalMap(normalize(local_position));
    vec3 color = min(vec3(1000.0), texture(equirectangular_map, uv).rgb);

    out_color = vec4(color, 1.0);
}
