#pragma once
#include "TextureLoader.h"
#include "Texture.h"
#include <map>
#include <string>

using std::string;
using std::map;

namespace Voxels {
	class TextureCache {
	public:
		TextureCache();
		~TextureCache();
		Texture *getTexture(string texturePath, int rows, int columns);
		void updateCache();
	private:
		map<string, Texture *> textureMap;
	};
}
