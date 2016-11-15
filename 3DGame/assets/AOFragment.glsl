in vec3 fPos;
in vec4 fPosL;
flat in int fType;

uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform mat4 lightVP;
uniform mat4 InverseProjection;

uniform sampler2D texture;
uniform sampler2D atlas;
uniform sampler2D depth;

const float near = 0.1;
const float far = 1000.;
const float PI = 3.1415926;
float radius;
float intensity = 1.;
float scale = 0.2;
float bias = 0.;
vec2 randomSize = vec2(64, 64);
vec2 kernel[4];

float linearDepth(float d){
	float z = 2. * d - 1.;
	return (2. * near * far) / (far + near - z*(far - near));
}

float getDepth(vec2 uv){
	return linearDepth(texture(depth, uv).x)/far;
}

float calcShadow(vec4 fPosL, float bias){
	vec3 proj = fPosL.xyz/fPosL.w;
	proj = proj * .5 + .5;
	float closest = texture(depth, proj.xy).r;
	float current = proj.z;
	return current - bias > closest ? 1. : 0.;
}

vec2 getRand(vec2 uv){
	return normalize(texture(texture, vec2(500, 500)*uv/randomSize).xy*2.-1.);
}

vec3 getPosition(vec2 uv){
	vec2 screen = uv * 2. - 1.;
	float depth = getDepth(uv);
	vec4 position = vec4(screen, 2.*depth-1., 1.);
	position = (InverseProjection * position);
	position /= position.w;
	position.z = -position.z;
	return position;
}

float doAO(vec2 tcoord, vec2 uv, vec3 pos, vec3 normal){
	vec3 diff = abs(getPosition(tcoord + uv) - pos);
	vec3 v = normalize(diff);
	float d = length(diff) * scale;
	return max(0., dot(normal, v) - bias) * (1. / (1. + d)) * intensity;
}

float calcAO(vec3 normal){
	vec2 uv = gl_FragCoord.xy/500.;
	vec2 rand = getRand(uv);
	float ao = 0.;
	float depth = getDepth(uv);
	radius = 0.5/sqrt(abs(fPos.z));
	for(int i = 0; i < 4; i++){
		vec2 k1 = reflect(kernel[i], rand) * radius;
		vec2 k2 = vec2(k1.x*.707 - k1.y*.707, k1.x*.707 + k1.y*.707);
		ao += doAO(uv, k1*.25, fPos, normal);
		ao += doAO(uv, k2*.5, fPos, normal);
		ao += doAO(uv, k1*.75, fPos, normal);
		ao += doAO(uv, k2, fPos, normal);
	}
	return ao/16.;
}

void main(){
	vec3 normal = normalize(cross(dFdx(fPos), dFdy(fPos)));
	vec3 lightDir = normalize(lightPos - fPos);
	vec3 viewDir = normalize(cameraPos - fPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	kernel[0] = vec2(0.);
	kernel[1] = vec2(0., 1.);
	kernel[2] = vec2(1., 0.);
	kernel[3] = vec2(1.);

	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	float shadow = calcShadow(fPosL, bias);
	float ambient = .85*calcAO(normal) + .15*(1.-shadow);
	float diffuse = 0.75 * max(abs(dot(normal, lightDir)), 0.);
	float specular = 0.45 * pow(max(dot(viewDir, reflectDir), 0.), 32.);
	
	vec2 uv = mod(fPos.xz, 1.0)/1.0;
	uv.x += mod(fType, 4.);
	uv.y += floor(fType / 4.);
	uv.x /= 4.;
	uv.y /= 4.;

	//gl_FragColor = vec4((ambient+diffuse+specular)*texture(atlas, uv).xyz, 1.);
	gl_FragColor = vec4(vec3(ambient), 1.);
}
