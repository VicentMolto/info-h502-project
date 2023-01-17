#version 330 core

out vec4 FragColor; // 输出为 vec4 

in vec3 Normal;
in vec2 UV;
in vec3 posWS;

uniform sampler2D t0;
uniform sampler2D t1;
uniform samplerCube cubemap;
uniform vec3 lPos = vec3(0,0,0);
uniform vec3 color;
uniform vec3 camPos;




void main() {

	
	vec3 nDir = normalize(Normal);
	vec3 lDir = normalize(lPos - posWS);
	float NoL = dot(nDir,lDir);
	NoL = max(0.25,NoL);

	vec4 t0 = texture(t0, UV);
	vec3 t1 = texture(t1, UV).xyz;
	// Specular
	vec3 rDir = reflect(-lDir,nDir);
	vec3 vDir = normalize(camPos-posWS);
	float spec = max(0,dot(vDir,rDir));
	spec = pow(spec,5);

// Fresnel
	float fresnel = 1-max(0,dot(vDir,nDir));
	

// 反射
	vec3 vr_refl = reflect(-vDir,nDir);
	vec3 cubemap_refl = texture(cubemap,vr_refl).xyz;
// 折射

	float ratio = 1.00 / 1.05;
	vec3  vr_refr = refract(-vDir,nDir,ratio);

	vec3 cubemap_refr = texture(cubemap,vr_refr).xyz;
	FragColor = vec4(fresnel*cubemap_refl+cubemap_refr*vec3(1,.5,0),1);	

}