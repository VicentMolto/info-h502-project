#version 330 core

out vec4 FragColor; // 输出为 vec4 

in vec3 UV;


uniform samplerCube t0;



void main() {

	vec4 t0 = texture(t0, UV);
	FragColor = vec4(t0);	

}