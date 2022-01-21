#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"
#include "stb_image.h"

unsigned char* TextureLoader::LoadImage(const std::string &InFileLocation, int &OutWidth, int &OutHeight, int &OutNrChannels)
{
	stbi_set_flip_vertically_on_load(false);
	return stbi_load(InFileLocation.c_str(), &OutWidth, &OutHeight, &OutNrChannels, 0);
}

void TextureLoader::ClearLoadedImageMemory(unsigned char* ImageData)
{
	stbi_image_free(ImageData);
}

