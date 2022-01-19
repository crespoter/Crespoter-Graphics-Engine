#pragma once

class ITextureInterface;

class Material
{
private:
	float Shininess = 32.0f;
	ITextureInterface* DiffuseTexture;
	ITextureInterface* SpecularTexture;
};