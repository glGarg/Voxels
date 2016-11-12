#include "TextureLoader.h"

namespace Voxels {
	Texture::Texture(int texture, int width, int height) : texture(texture), width(width), height(height) {
		TextureLoader::incrementTextureCount();
	}

	Texture::~Texture() {}

	void Texture::init() {
		glGenTextures(1, &id);
	}

	void Texture::bind() {
		glActiveTexture(GL_TEXTURE0 + texture);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::setSource(GLint level, GLint internalFormat, GLint format, GLint type, const GLvoid *data) {
		glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, 0, format, type, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	}

	Texture::operator GLuint() {
		return id;
	}
	
	int TextureLoader::textureCount = 0;

	int TextureLoader::getTextureCount() { return textureCount; }

	void TextureLoader::incrementTextureCount() { textureCount++; }

	void TextureLoader::freeImage(Texture *texture) {
		if (nullptr != texture) {
			free(texture);
		}
		//cannot do because last texture need not be deleted first
		//textureCount--;
	}

	Texture *TextureLoader::loadImage(string texturePath) {
		ifstream file(texturePath);
		if (!file) {
			//Incorrect file path
		}
		int width, height;
		unsigned char *image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		
		Texture *texture = new Texture(textureCount, width, height);
		texture->init();
		texture->bind(); //maybe wanna bind this before draw
		texture->setSource(0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		textureCount++;
		SOIL_free_image_data(image);
		return texture;
	}
}
