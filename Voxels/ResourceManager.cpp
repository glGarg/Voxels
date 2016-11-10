#include "ResourceManager.h"

namespace Voxels {
	TextureCache ResourceManager::textureCache;

	Texture *ResourceManager::getTexture(string texturePath) {
		return textureCache.getTexture(texturePath);
	}
}