layout (location = 0) in vec3 position;

uniform mat4 lightVP;

void main(){
	gl_Position = lightVP * vec4(position, 1.);
}