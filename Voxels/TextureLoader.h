#pragma once
#include <iostream>
#include <SOIL.h>
#include <fstream>
#include "Texture.h"

using std::string;
using std::ifstream;

namespace Voxels {
	class TextureLoader {
	public:
		static Texture *loadImage(string texturePath);
		static void freeImage(Texture *texture);
		static int getTextureCount();
	private:
		static int textureCount;
	};
}
