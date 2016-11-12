layout(location = 0) in vec3 position;

uniform mat4 MVP;

flat out vec3 fUv;
smooth out vec3 fPos;
out float fZ;

void main(){
	vec4 pos = MVP * vec4(position, 1.);
	fUv = position;
	fPos = position;
	fZ = pos.w;
	gl_Position = pos;
}