#include "TextureCache.h"

namespace Voxels {
	TextureCache::TextureCache() {}

	TextureCache::~TextureCache() {
		for (map<string, Texture *>::iterator it = textureMap.begin(); it != textureMap.end(); it++) {
			if (nullptr != it->second) {
				TextureLoader::freeImage(it->second);
			}
		}
	}

	void TextureCache::updateCache() {
		//Add multi-threading later
		//called every 10 min by resource manager to update the textures
		for (map<string, Texture *>::iterator it = textureMap.begin(); it != textureMap.end(); it++) {
			if (nullptr != it->second) {
				TextureLoader::freeImage(it->second);
			}
			textureMap[it->first] = TextureLoader::loadImage(it->first, it->second->rows, it->second->columns);
		}
	}

	Texture *TextureCache::getTexture(string texturePath, int rows, int columns) {
		map<string, Texture *>::iterator it = textureMap.find(texturePath);
		if (it == textureMap.end()) {
			Texture *texture = TextureLoader::loadImage(texturePath, rows, columns);
			textureMap[texturePath] = texture;
			return texture;
		}
		else {
			return it->second;
		}
	}
}
