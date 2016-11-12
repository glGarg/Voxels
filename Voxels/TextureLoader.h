#pragma once
#include <gl/glew.h>
#include <iostream>
#include <SOIL.h>
#include <fstream>
#include "Texture.h"

using std::string;
using std::ifstream;

namespace Voxels {
	struct Texture {
		Texture(int texture, int width, int height);
		~Texture();
		void init();
		void bind();
		void setSource(GLint level, GLint internalFormat, GLint format, GLint type, const GLvoid *data);
		operator GLuint();

		GLuint id;
		int texture;
		int width, height;
	};

	class TextureLoader {
	public:
		static Texture *loadImage(string texturePath);
		static void freeImage(Texture *texture);
		static int getTextureCount();
		static void incrementTextureCount();
	private:
		static int textureCount;
	};
}
