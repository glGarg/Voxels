#include "ResourceManager.h"

namespace Voxels {
	TextureCache ResourceManager::textureCache;

	Texture *ResourceManager::getTexture(string texturePath) {
		return textureCache.getTexture(texturePath, 1, 1);
	}
	Texture *ResourceManager::getTextureAtlas(string texturePath, int rows, int columns) {
		return textureCache.getTexture(texturePath, rows, columns);
	}
}