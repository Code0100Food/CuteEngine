#version 330 core

uniform sampler2D bright_pixels_texture;
uniform int mipmap_level;
uniform bool is_vertical_blur;

out vec4 outColor;

vec4 PassVerticalBlur(float kernel[6])
{
	vec2 viewportSize = textureSize(bright_pixels_texture, mipmap_level);
	vec2 texCoords = gl_FragCoord.xy / viewportSize;
	float texIncrement_y = 1.0 / viewportSize.y;

	vec3 ret_color = textureLod(bright_pixels_texture, texCoords, mipmap_level).rgb * kernel[0];

	float sum = kernel[0];

	for(int i = 1; i < 6; i++)
	{
		ret_color += textureLod(bright_pixels_texture, texCoords + vec2(0.0, texIncrement_y * i), mipmap_level).rgb * kernel[i];
		ret_color += textureLod(bright_pixels_texture, texCoords - vec2(0.0, texIncrement_y * i), mipmap_level).rgb * kernel[i];
		sum += kernel[i] * 2;
	}

	ret_color /= sum;
	return vec4(ret_color.rgb, 1.0);
}

vec4 PassHorizontalBlur(float kernel[6])
{
	vec2 viewportSize = textureSize(bright_pixels_texture, mipmap_level);
	vec2 texCoords = gl_FragCoord.xy / viewportSize;
	float texIncrement_x = 1.0 / viewportSize.x;

	vec3 ret_color = textureLod(bright_pixels_texture, texCoords, mipmap_level).rgb * kernel[0];

	float sum = kernel[0];

	for(int i = 1; i < 6; i++)
	{
		ret_color += textureLod(bright_pixels_texture, texCoords + vec2(texIncrement_x* i, 0.0), mipmap_level).rgb * kernel[i];
		ret_color += textureLod(bright_pixels_texture, texCoords - vec2(texIncrement_x* i, 0.0), mipmap_level).rgb * kernel[i];
		sum += kernel[i] * 2;
	}

	ret_color /= sum;
	return vec4(ret_color.rgb, 1.0);
}

void main(void)
{
	float kernel[6];
	kernel[0] = 1.0; //Current Pixel
	kernel[1] = 0.035822;
	kernel[2] = 0.05879;
	kernel[3] = 0.086425;
	kernel[4] = 0.113806;
	kernel[5] = 0.13424;

	if(is_vertical_blur)
	{


		outColor = PassVerticalBlur(kernel);

	}
	else
	{
		outColor = PassHorizontalBlur(kernel);
	}

}
