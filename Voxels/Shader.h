#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/GL.h>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

namespace Voxels {
	class Shader
	{
	public:
		Shader();
		Shader(string filePath, GLenum shaderKind);
		~Shader();
		operator GLuint();
	private:
		void compile();
		GLuint shader;
	};
}