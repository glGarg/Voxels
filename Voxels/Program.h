#pragma once
#include <GL/glew.h>
#include <GL/GL.h>
#include "Shader.h"

namespace Voxels {
	class Program
	{
	public:
		Program();
		~Program();
		void attach(Shader &shader);
		void link();
		void use();
		void disable();
		GLint getUniformLocation(string uniform);
		operator GLuint();
	private:
		GLuint program;
	};

}