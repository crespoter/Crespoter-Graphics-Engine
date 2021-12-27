#include "OpenGLTexture.h"
#include <glad/glad.h>
#include<iostream>
#include <GLFW/glfw3.h>
#include <assert.h>
#include "../TextureLoader/TextureLoader.h"
#include "../../ShaderProgram/ShaderProgram.h"

COpenGLTexture::COpenGLTexture(const std::string &InFileLocation)
{
	LoadTexture(InFileLocation);
}

void COpenGLTexture::LoadTexture(const std::string& InFilePath)
{
	unsigned char* TextureData = TextureLoader::LoadImage(InFilePath, TextureInfo.Width, TextureInfo.Height, TextureInfo.NRChannels);
	if (!TextureData)
	{
		std::cout << "Failed to load Texture file " << InFilePath << std::endl;
		return;
	}
	glGenTextures(1, &TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureInfo.Width, TextureInfo.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
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

