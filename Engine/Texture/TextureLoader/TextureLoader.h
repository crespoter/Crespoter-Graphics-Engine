#pragma once
#include <iostream>

/**
 * Static class for loading images
 */
class TextureLoader
{
public:
	static unsigned char* LoadImage(const std::string& InFileLocation, int& OutWidth, int& OutHeight, int& OutNrChannels);
	static void ClearLoadedImageMemory(unsigned char* ImageData);

private:
	TextureLoader() {};
};