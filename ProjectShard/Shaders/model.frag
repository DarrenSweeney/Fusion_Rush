#version 330

out vec4 color;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
	color = vec4(texture(texture_diffuse1, TexCoords));
}