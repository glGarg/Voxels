in vec3 fPos;
in vec4 fPosL;
flat in int fType;

uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform mat4 lightVP;

uniform sampler2D texture;
uniform sampler2D atlas;
uniform sampler2D depth;

const float near = 0.1;
const float far = 1000.;
const float PI = 3.1415926;

//#define DEBUG_DEPTH

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

vec2 kernel[4];

float Hash( float n ){
    return fract(sin(n)*3375.545383);
}

vec3 Noise( in vec2 x ){
	x+=4.2;
    vec2 p = floor(x);
    vec2 f = fract(x);

    vec2 u = f*f*f*(6.0*f*f - 15.0*f + 10.0);
    float n = p.x + p.y*507.0;

    float a = Hash(n+  0.0);
    float b = Hash(n+  1.0);
    float c = Hash(n+ 507.0);
    float d = Hash(n+ 508.0);
    return 1.3*vec3(a+(b-a)*u.x+(c-a)*u.y+(a-b-c+d)*u.x*u.y,
				6.0*f*(f-1.0)*(vec2(b-a,c-a)+(a-b-c+d)*u.yx));
}
/*float radius = 3. * (1. - linearDepth(texture(depth, gl_FragCoord.xy).x)/far);
	vec3 rand = 2. * texture(texture, gl_FragCoord.xy).xyz - 1.;
	mat2 rot45 = mat2(cos(PI/4), sin(PI/4),
					 -sin(PI/4), cos(PI/4));
	vec3 tangent = normalize(rand - normal * dot(rand, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 TBN = mat3(tangent, bitangent, normal);  
	float texelSize = 1./vec2(500., 500.).x;//textureSize(depth, 0.);
	for(int i = 0; i < 4; i++){
		vec3 sample = TBN * kernel[i];
		sample = gl_FragCoord.xyz + sample * radius;
		vec4 offset = vec4(sample, 1.);
		offset = lightVP * offset;
		offset.xyz /= offset.w;
		offset.xyz = offset.xyz * .5 + .5;
		float sampleDepth = -texture(depth, offset.xy).w;
		float rangeCheck = smoothstep(0., 1., radius/abs(gl_FragCoord.z - sampleDepth));
		ao += (sampleDepth > sample.z ? 1. : 0.) * rangeCheck;
		//vec2 k1 = reflect(kernel[i], rand);
		//vec2 k2 = rot45 * rand;
		//k1 *= texelSize;
		//k2 *= texelSize;
		//ao += linearDepth(texture(depth, gl_FragCoord.xy + k1*radius).x/far);
		//ao += linearDepth(texture(depth, gl_FragCoord.xy + k2*radius * .75).x/far);
		//ao += linearDepth(texture(depth, gl_FragCoord.xy + k1*radius * .50).x/far);
		//ao += linearDepth(texture(depth, gl_FragCoord.xy + k2*radius * .25).x/far);
	}*/
float Hash12(vec2 p){
	vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}
vec3 calcAO(vec3 normal){
	vec3 ao = vec3(0.);
	vec2 uv = gl_FragCoord.xy;
	vec2 rand = vec2(Hash12(uv.xy), Hash12(uv.yx));
	float depth = getDepth(uv);
	float radius = .2/sqrt(abs(depth));
	for(int i = 0; i < 4; i++){
		vec2 k1 = reflect(kernel[i], rand);
		vec2 k2 = vec2(k1.x*.707 - k1.y*.707, k1.x*.707 + k1.y*.707);
		//ao += calc_ao(uv, k1*.25, fPos, normal);//getDepth(uv + k1*radius*.25);
		//ao += calc_ao(uv, k1*.5, fPos, normal);//getDepth(uv + k2*radius*.50);
		//ao += calc_ao(uv, k1*.75, fPos, normal);//getDepth(uv + k1*radius*.75);
		//ao += calc_ao(uv, k2, fPos, normal);//getDepth(uv + k2*radius);
	}
	//ao /= 32.;
	//ao = 1. - ao/8.;
	return 100.*ao;
}

void main(){
	vec3 normal = normalize(cross(dFdx(fPos), dFdy(fPos)));
	vec3 lightDir = normalize(lightPos - fPos);
	vec3 viewDir = normalize(cameraPos - fPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	kernel[0] = vec2(0.);//Noise(fPos.xz + vec2(0.));
	kernel[1] = vec2(0., 1.);//Noise(fPos.xz + vec2(0., 1.));
	kernel[2] = vec2(1., 0.);//Noise(fPos.xz + vec2(1., 0.));
	kernel[3] = vec2(1.);//Noise(fPos.xz + vec2(1., 1.));

	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	float shadow = calcShadow(fPosL, bias);
	float ambient = .15 * (1. - shadow);
	float diffuse = 0.75 * max(abs(dot(normal, lightDir)), 0.);
	float specular = 0.45 * pow(max(dot(viewDir, reflectDir), 0.), 32.);
	
	vec2 uv = mod(fPos.xz, 1.0)/1.0;
	uv.x += mod(fType, 4.);
	uv.y += floor(fType / 4.);
	uv.x /= 4.;
	uv.y /= 4.;

	gl_FragColor = vec4((ambient+diffuse+specular)*texture(atlas, uv).xyz, 1.);

#ifdef DEBUG_DEPTH
	gl_FragColor = vec4(vec3(linearDepth(texture(texture, gl_FragCoord.xy/500.).x)/far), 1.);
	//gl_FragColor = vec4(ambient, 1.);
#endif
}
