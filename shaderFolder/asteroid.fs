#version 330 core
out vec4 FragColor; // 输出为 vec4 

in vec2 UV;
in vec3 Normal;
in vec3 posWS;
uniform vec3 lPos = vec3(10,20,30);
uniform sampler2D t0;



void main() {

	vec3 nDir = normalize(Normal);
	vec3 lDir = normalize(lPos - posWS);
	float NoL = dot(nDir,lDir);
	NoL = max(0.25,NoL);

	vec4 t0 = texture(t0, UV);
	FragColor = vec4(t0.xyz*NoL,1);	

}