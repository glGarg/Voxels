layout (location = 0) in vec3 position;
layout (location = 1) in int type;
layout (location = 2) in float AO;

uniform vec3 lightPos;
uniform mat4 MVP;
uniform mat4 lightVP;

smooth out vec3 fPos;
out vec4 fPosL;
flat out int fType;
smooth out float fAO;

void main(){
	fPos = position;
	fPosL = lightVP * vec4(position, 1.);
	fType = type;
	fAO = AO;
	gl_Position = MVP * vec4(position, 1.);
}