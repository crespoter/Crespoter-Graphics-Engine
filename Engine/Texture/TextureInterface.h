#pragma once
#include <iostream>

class CShaderProgram;

/**
 * Interface class for loading textures into GPU
 */
class ITextureInterface
{
public:
	struct FTextureInfo
	{
		int Width = 0;
		int Height = 0;
		int NRChannels = 0;
	};
protected:
	ITextureInterface() {};
	FTextureInfo TextureInfo = FTextureInfo();
public:
	virtual void LoadTexture(const std::string &InFilePath) = 0;

	virtual void BindTexture(CShaderProgram* ShaderProgram, const std::string &UniformName, int TextureUnit) = 0;
};