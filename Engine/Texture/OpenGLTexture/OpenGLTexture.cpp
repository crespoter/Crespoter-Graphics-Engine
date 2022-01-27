#include "OpenGLTexture.h"
#include <glad/glad.h>
#include<iostream>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "../TextureLoader/TextureLoader.h"
#include "../../ShaderProgram/ShaderProgram.h"

COpenGLTexture::COpenGLTexture(const std::string& InFileLocation)
{
	LoadTexture(InFileLocation);
}

void COpenGLTexture::LoadTexture(const std::string& InFilePath)
{
	unsigned char* TextureData = TextureLoader::LoadImage(InFilePath, TextureInfo.Width, TextureInfo.Height, TextureInfo.NRChannels);
	if (!TextureData)
	{
		std::cout << "Failed to load Texture file " << InFilePath << std::endl;
		// Load default texture here
		TextureData = TextureLoader::LoadImage(ShaderConstants::TEXTURE_NOT_FOUND_TEXTURE, TextureInfo.Width, TextureInfo.Height, TextureInfo.NRChannels);
	}
	GLenum TextureFormat = -1;
	switch (TextureInfo.NRChannels)
	{
	case 1:
		TextureFormat = GL_RED;
		break;
	case 3:
		TextureFormat = GL_RGB;
		break;
	case 4:
		TextureFormat = GL_RGBA;
		break;
	}

	assert(TextureFormat != -1); // The texture type is unidentified.

	glGenTextures(1, &TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, TextureFormat, TextureInfo.Width, TextureInfo.Height, 0, TextureFormat, GL_UNSIGNED_BYTE, TextureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	TextureLoader::ClearLoadedImageMemory(TextureData);
	bIsInitialized = true;
}

void COpenGLTexture::BindTexture(CShaderProgram* ShaderProgram, const std::string& UniformName, int TextureUnit)
{
	assert(bIsInitialized);
	glActiveTexture(GL_TEXTURE0 + TextureUnit);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	ShaderProgram->SetInteger(UniformName, TextureUnit);
}

