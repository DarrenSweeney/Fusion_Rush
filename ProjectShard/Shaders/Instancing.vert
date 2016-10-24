#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;
out float visibility;

const float density = 0.0015;
const float gradient = 1.5;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec4 worldPosition = instanceMatrix * vec4(position, 1.0f);
	vec4 positionRelativeToCam = view * worldPosition;
	gl_Position = projection * positionRelativeToCam;
    TexCoords = texCoords;

	float distance = length(positionRelativeToCam.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}