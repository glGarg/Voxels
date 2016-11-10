#pragma once
#include <GL/glew.h>

namespace Voxels {
	struct Texture {
		GLuint id;
		int texture;
		int width, height;
		operator GLuint();
	};
}
