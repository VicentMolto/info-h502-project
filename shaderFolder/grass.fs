#version 330 core

out vec4 FragColor; // 输出为 vec4 

in vec3 Normal;
in vec2 UV;
in vec3 posWS;

uniform sampler2D t0;
uniform sampler2D t1;
uniform vec3 lPos = vec3(0,0,0);
uniform vec3 color;
uniform vec3 camPos;


float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

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
	float depth = LinearizeDepth(gl_FragCoord.z)/far;
	FragColor = vec4(vec3(depth),1);
	if(t0.a < 0.2)
       discard;
	 FragColor = vec4(t0*NoL);	


}