#ifndef PERHAPS_IMPORTER
#define PERHAPS_IMPORTER
#include "../../PerhapsPch.h"
#include "../Graphics/Texture2D.h"

namespace Perhaps
{
	class Importer
	{
		public:
			static Texture2D* ImportTexture(const std::string& filePath, bool flip)
			{
				int width, height, nrChannels;
				stbi_set_flip_vertically_on_load(flip);
				unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

				Texture2D* tex = new Texture2D(width, height, data, nrChannels);
				tex->Apply();
				stbi_image_free(data);

				return tex;
			}
	};
}

#endif