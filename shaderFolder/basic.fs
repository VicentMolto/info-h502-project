#version 330 core

out vec4 FragColor; // 

in vec3 Normal;
in vec2 UV;
in vec3 posWS;

uniform sampler2D t0;
uniform sampler2D t1;
uniform vec3 lPos = vec3(10,100,30);
uniform vec3 color;
uniform vec3 camPos;

void main() {

	
	vec3 nDir = normalize(Normal);
	vec3 lDir = normalize(lPos - posWS);
	float NoL = dot(nDir,lDir);
	NoL = max(0.25,NoL);

	vec3 t0 = texture(t0, UV).xyz;
	vec3 t1 = texture(t1, UV).xyz;
	// Specular
	vec3 rDir = reflect(-lDir,nDir);
	vec3 vDir = normalize(camPos-posWS);
	float spec = max(0,dot(vDir,rDir));
	spec = pow(spec,5);
	FragColor = vec4(t0*NoL+t1* spec,1);	


}