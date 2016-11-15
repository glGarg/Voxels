layout (location = 0) in vec3 position;
layout (location = 1) in int type;

uniform mat4 MVP;

smooth out vec3 fPos;
flat out int fType;

void main(){
	vec4 pos = MVP * vec4(position, 1.);
	fPos = position;
	fType = type;
	gl_Position = pos;
}