#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 color;
	vec4 offset;
} gs_in[];

out vec3 fColor;

void main() 
{    
    fColor = gs_in[0].color;

    gl_Position = gl_in[0].gl_Position + gs_in[0].offset;
    EmitVertex();
	gl_Position = gl_in[0].gl_Position - gs_in[0].offset;
	EmitVertex();

	 gl_Position = gl_in[0].gl_Position + vec4(0.0f, -5.0f, 0.0f, 0.0f);
    EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.0f, 5.0f, 0.0f, 0.0f);
	EmitVertex();

	 gl_Position = gl_in[0].gl_Position + vec4(0.0f, 0.0f, -5.0f, 0.0f);
    EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.0f, 0.0f, 5.0f, 0.0f);
	EmitVertex();

    EndPrimitive();
}