#include "Texture.h"

namespace Voxels {
	Texture::operator GLuint() {
		return id;
	}
}