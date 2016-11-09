#include "Program.h"

namespace Voxels {
	Program::Program() : program(glCreateProgram()) {}

	Program::~Program() {
		glDeleteProgram(program);
	}

	void Program::attach(Shader &shader) {
		glAttachShader(program, shader);
	}

	void Program::link() {
		glLinkProgram(program);
	}

	void Program::use() {
		glUseProgram(program);
	}

	void Program::disable() {
		glUseProgram(0);
	}

	GLint Program::getUniformLocation(string uniform) {
		return glGetUniformLocation(program, uniform.c_str());
	}

	Program::operator GLuint() {
		return program;
	}
}