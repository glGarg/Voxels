#include "Shader.h"

namespace Voxels {
	Shader::Shader() {
		//Error for no filepath specified
	}

	Shader::~Shader() {
		glDeleteShader(shader);
	}

	Shader::Shader(string filePath, GLenum shaderType) {
		ifstream shaderFile(filePath);
		if (shaderFile) {
			string shaderCode, line;
			const char *code = NULL;
			shader = glCreateShader(shaderType);
			while (getline(shaderFile, line)) {
				shaderCode += line + "\n";
			}
			code = shaderCode.c_str();
			glShaderSource(shader, 1, &code, NULL);
		}
		else {
			cout << "Invalid filepath: " << filePath << endl;
			//Error for invalid filepath
		}
		compile();
	}

	Shader::operator GLuint() {
		return shader;
	}
	void Shader::compile() {
		glCompileShader(shader);
#if DEBUG_GLSL
		GLint length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		vector<GLchar> errorLog(length);
		glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
		int i = 0;
		while (errorLog[i]) {
			std::cout << errorLog[i++];
		}
#endif
	}
}