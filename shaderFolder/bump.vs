#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec2 aUV;

out vec2 UV;
out vec3 Normal;
out vec3 Tangnet;
out vec3 posWS;
out mat3 TBN; // 把normal贴图 -> 世界空间的法线 (nDirTS - nDirWS)

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform bool reverse_n;

void main()
{
    UV = aUV;
    Tangnet =mat3(transpose(inverse(M))) * aTangent; // 世界空间的 Tangent
    Normal = mat3(transpose(inverse(M))) * aNormal;  //世界Normal nDirWS  
    vec3 B = cross(Tangnet, Normal);

    TBN = mat3(Tangnet,B,Normal);

    posWS =(M*vec4(aPos, 1.0)).xyz;  // 世界空间pos   posWS
    gl_Position = P*V*M*vec4(aPos , 1.0);
}