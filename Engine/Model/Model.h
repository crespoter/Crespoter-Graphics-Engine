#pragma once
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Texture/OpenGLTexture/OpenGLTexture.h"
#include "Mesh/Mesh.h"
#include <map>

class CModel
{
public:
	CModel(const std::string& ModelPath);
	void Draw(CShaderProgram* Shader);
private:
	std::string ModelFilePath;
	std::vector<CMesh> Meshes;
	std::map<std::string, COpenGLTexture> LoadedTexturesMap;

	void ProcessNode(aiNode* AssimpNode, const aiScene* AssimpScene);
	CMesh ProcessMesh(aiMesh* AssimpMesh, const aiScene* AssimpScene);
	std::vector<COpenGLTexture> LoadMaterialTextures(aiMaterial* AssimpMaterial, aiTextureType AssimpTextureType, ETextureType TextureType);
};