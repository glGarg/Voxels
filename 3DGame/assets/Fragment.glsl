in vec3 fPos;
flat in vec3 fUv;
in float fZ;

uniform vec3 lightPos; //light attached to camera
uniform mat4 lightPV;
uniform sampler2D texture;
uniform sampler2D depth;

const float near = 0.1;
const float far = 1000.;

float linearDepth(float d){
	float z = 2. * d - 1.;
	return (2. * near * far) / (far + near - z*(far - near));
}

void main(){
	vec3 normal = normalize(cross(dFdx(fPos), dFdy(fPos)));
	vec3 lightDir = normalize(lightPos - fPos);
	vec3 viewDir = normalize(lightPos - fPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float ambient = 0.1;
	float diffuse = 0.6 * max(abs(dot(normal, lightDir)), 0.);
	float specular = pow(max(dot(viewDir, reflectDir), 0.), 32.);
	
	gl_FragColor = vec4((ambient+diffuse+specular) * vec3(2., 1., 0.), 1.);
	if(normal.y >= 0.8)
		gl_FragColor = vec4(texture(texture, vec2(mod(fPos.xz, 16.)/16.)).xyz, 1.);
	
	vec3 origin = fPos;

	float z = linearDepth(gl_FragCoord.z)/far;
	//gl_FragColor = vec4(vec3(sin(texture(depth, gl_FragCoord.xy/500.).x)), 1.);
	gl_FragColor = vec4(vec3(linearDepth(texture(depth, gl_FragCoord.xy/500.).x)/far), 1.);
}
