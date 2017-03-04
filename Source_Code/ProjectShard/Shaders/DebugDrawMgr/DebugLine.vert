#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 projection;
uniform mat4 view;

out VS_OUT {
    vec3 color;
} vs_out;

void main()
{
    gl_Position = projection * view * vec4(position, 1.0f);
    vs_out.color = color;
}