#version 330 core

in Data
{
	vec2 UV_coords;
}FSIn;

vec4 normalized_device_coordinate;
uniform int viewport_width;
uniform int viewport_height;
uniform float near;
uniform float far;
uniform mat4 projection_matrix_transposed;
uniform mat4 view_matrix_transposed;

uniform sampler2D color_texture;
uniform sampler2D normal_texture;
uniform vec3 camera_position;

uniform vec3 light_direction;
uniform vec4 light_color;
uniform int light_intensity;

uniform int light_type;
out vec4 outShadedColor;

vec3 FragmentToWorld()
{
	//Transform FragmentPos to WorldPos
	vec2 viewport_size = vec2(viewport_width, viewport_height);
	normalized_device_coordinate.xy = ((2.0 * gl_FragCoord.xy) / viewport_size.xy) - 1;
	normalized_device_coordinate.z = ((2.0 * gl_FragCoord.z) - far - near) / (far - near);
	normalized_device_coordinate.w = 1.0;

	normalized_device_coordinate  = normalized_device_coordinate / gl_FragCoord.w;
	vec3 world_space_fragment = (view_matrix_transposed * projection_matrix_transposed * normalized_device_coordinate ).xyz; 

	return world_space_fragment;
}

vec4 CalculateDirectional()
{
	vec3 light_dir_normalized = normalize(light_direction);

	vec4 albedo_color = texture(color_texture, FSIn.UV_coords);
	vec3 normal_vector = texture(normal_texture, FSIn.UV_coords).xyz;
	
	vec3 eye_dir = normalize(camera_position - FragmentToWorld());
	vec3 H = normalize(eye_dir + light_dir_normalized );
		

	vec4 ambient_color =  vec4(albedo_color.rgb * 0.05, 1.0);
	vec4 difuse_color = albedo_color * dot(normal_vector, light_dir_normalized );
	vec4 specular =  0.5 * pow(max(dot(normal_vector  , H), 0.0), 32) * light_color;

	return ((ambient_color + difuse_color) * light_color) + specular;
}

vec4 CalculatePoint()
{
	return vec4(1.0);
}

void main(void)
{
	if(light_type == 0)
		outShadedColor = vec4(CalculateDirectional().xyz * (light_intensity * 0.1), 1.0);

	if(light_type == 1)
		outShadedColor = CalculatePoint();
}
