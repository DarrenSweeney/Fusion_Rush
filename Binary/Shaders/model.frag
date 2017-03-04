#version 330

out vec4 color;
in vec2 TexCoords;
in float visibility;

uniform vec3 skyColour;
uniform sampler2D texture_diffuse1;

void main()
{
	color = vec4(texture(texture_diffuse1, TexCoords));
	color = mix(vec4(skyColour, 1.0), color, visibility);
}