#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 texCoords;
} vs_out;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main()
{
    vs_out.texCoords = aTexCoords;
    gl_Position = P * V * M * vec4(aPos, 1.0); 
}