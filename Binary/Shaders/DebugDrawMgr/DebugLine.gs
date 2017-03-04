#version 330 core
layout (lines) in;
layout (line_strip, max_vertices = 2) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

void main() 
{    
    fColor = gs_in[0].color;

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    EndPrimitive();
}