#pragma once
#include "TextureCache.h"
#include "TextureLoader.h"

using std::string;

namespace Voxels {
	class ResourceManager {
	public:
		static Texture *getTexture(string texturePath);
	private:
		static TextureCache textureCache;
	};
}