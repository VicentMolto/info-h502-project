#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float lenth = 1;

uniform mat4 V;
uniform mat4 P;

void GenerateLine(int index)
{
    gl_Position = P *V* gl_in[index].gl_Position;
    EmitVertex();

    gl_Position = P * V*(gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * lenth);
    EmitVertex();

    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}