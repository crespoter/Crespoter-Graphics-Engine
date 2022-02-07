#pragma once
#include "../TextureInterface.h"


class COpenGLTexture : public ITextureInterface
{
public:
	COpenGLTexture() {};
	COpenGLTexture(const std::string& InFileLocation);

	void LoadTexture(const std::string& InFilePath) override;

	void BindTexture(CShaderProgram* ShaderProgram, const std::string& UniformName, int TextureUnit) override;

private:
	unsigned int TextureID = 0;
	bool bIsInitialized = false;
};