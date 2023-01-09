#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in mat4 instanceMatrix;

out vec2 UV;
out vec3 Normal;
out vec3 posWS;

uniform mat4 P;
uniform mat4 V;

void main()
{
    UV = aUV;
    Normal = mat3(transpose(inverse(instanceMatrix))) * aNormal;
    posWS =(instanceMatrix*vec4(aPos, 1.0)).xyz;
    gl_Position = P * V * instanceMatrix * vec4(aPos, 1.0); 
}