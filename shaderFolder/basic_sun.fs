#version 330 core

out vec4 FragColor; // 

in vec3 Normal;
in vec2 UV;
in vec3 posWS;

uniform sampler2D t0;
uniform sampler2D t1;
uniform vec3 lPos = vec3(0,0,0);
uniform vec3 color;
uniform vec3 camPos;

void main() {


	vec3 t0 = texture(t0, UV).xyz;
	vec3 t1 = texture(t1, UV).xyz;
	FragColor = vec4(t0+t1,1);	


}