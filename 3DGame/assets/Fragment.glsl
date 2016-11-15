in vec3 fPos;
flat in int fType;

uniform vec3 lightPos; //light attached to camera
uniform mat4 lightPV;
uniform sampler2D texture;
uniform sampler2D atlas;
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
	
	vec2 uv = mod(fPos.xz, 1.0)/1.0;
	uv.x += mod(fType, 4.);
	uv.y += floor(fType / 4.);
	uv.x /= 4.;
	uv.y /= 4.;
	
	gl_FragColor = vec4((ambient+diffuse+specular) * vec3(2., 1., 0.), 1.);
	if(normal.y >= 0.8)
		gl_FragColor = vec4(texture(atlas, uv).xyz, 1.);
	
	//gl_FragColor = vec4(vec3(sin(texture(depth, gl_FragCoord.xy/500.).x)), 1.);
	//gl_FragColor = vec4(vec3(linearDepth(texture(texture, gl_FragCoord.xy/500.).x)/far), 1.);
}
