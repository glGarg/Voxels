#include "Framebuffer.h"

namespace Voxels {
	Framebuffer::Framebuffer() {}

	Framebuffer::~Framebuffer()	{}

	void Framebuffer::init() {
		glGenFramebuffers(1, &id);
	}
	
	void Framebuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}
	
	void Framebuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void Framebuffer::attachTexture(GLint attachment, GLuint texture, GLint level) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, level);
	}
	
	void Framebuffer::drawBuffer(GLint mode) {
		glDrawBuffer(mode);
	}
	
	void Framebuffer::readBuffer(GLint mode) {
		glReadBuffer(mode);
	}
}
