#include "TextureLoader.h"

namespace Voxels {
	int TextureLoader::textureCount = 0;

	int TextureLoader::getTextureCount() { return textureCount; }

	void TextureLoader::freeImage(Texture *texture) {
		if (nullptr != texture) {
			free(texture);
		}
		textureCount--;
	}

	Texture *TextureLoader::loadImage(string texturePath) {
		Texture *texture = new Texture;
		texture->texture = textureCount;
		ifstream file(texturePath);
		if (!file) {
			//Incorrect file path
		}
		unsigned char *image = SOIL_load_image(texturePath.c_str(), &(texture->width), &(texture->height), 0, SOIL_LOAD_RGBA);
		glGenTextures(1, &(texture->id));
		glActiveTexture(GL_TEXTURE0 + textureCount);
		glBindTexture(GL_TEXTURE_2D, *texture); //maybe wanna bind this before draw
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		textureCount++;
		SOIL_free_image_data(image);
		return texture;
	}
}
