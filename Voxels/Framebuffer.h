#pragma once
#include <gl/glew.h>

namespace Voxels {
	class Framebuffer {
	public:
		Framebuffer();
		~Framebuffer();
		void init();
		void bind();
		void unbind();
		void attachTexture(GLint attachment, GLuint texture, GLint level);
		void drawBuffer(GLint mode);
		void readBuffer(GLint mode);
	private:
		GLuint id;
	};
}