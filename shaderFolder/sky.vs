#version 330 core
layout(location = 0) in vec3 aPos; // 数据里第0个 vec3 是 Position
layout(location = 1) in vec3 aNormal; // 数据里第0个 vec3 是 Position
layout(location = 2) in vec2 aUV; // 数据里第0个 vec3 是 Position

out vec3 UV;

uniform mat4 V;
uniform mat4 P;

void main()
{	
	UV = aPos;
    vec4 pos = P * V * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}

