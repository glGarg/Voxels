#pragma once
#include "TextureCache.h"
#include "TextureLoader.h"

using std::string;

namespace Voxels {
	class ResourceManager {
	public:
		static Texture *getTexture(string texturePath);
		static Texture *getTextureAtlas(string texturePath, int rows, int columns);
	private:
		static TextureCache textureCache;
	};
}