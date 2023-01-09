#version 330 core
layout(location = 0) in vec3 aPos; // 数据里第0个 vec3 是 Position
layout(location = 1) in vec3 aNormal; // 数据里第0个 vec3 是 Position
layout(location = 2) in vec2 aUV; // 数据里第0个 vec3 是 Position

out vec3 Normal;
out vec2 UV;
out vec3 posWS;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{	
	Normal = mat3(transpose(inverse(M))) * aNormal;
	UV = aUV;
	posWS = (M*vec4(aPos, 1.0)).xyz;
	
	gl_Position =   P * V * M * vec4(aPos, 1.0); // 矩阵 * 点
	//gl_Position =  vec4(aPos, 1.0); // 矩阵 * 点
}

