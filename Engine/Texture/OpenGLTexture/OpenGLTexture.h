#pragma once
#include "../TextureInterface.h"

class COpenGLTexture : public ITextureInterface
{
private:
	unsigned int TextureID = 0;
	bool bIsInitialized = false;
public:
	COpenGLTexture() {};
	COpenGLTexture(const std::string &InFileLocation);

	void LoadTexture(const std::string& InFilePath) override;

	void BindTexture(CShaderProgram* WindowRef, const std::string& UniformName, int TextureUnit) override;

};