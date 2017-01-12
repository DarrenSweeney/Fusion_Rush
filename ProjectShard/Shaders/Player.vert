#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out VS_OUT {
    vec2 texCoords;
} vs_out;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); 
    vs_out.texCoords = texCoords;
	//TexCoords = texCoords;
}