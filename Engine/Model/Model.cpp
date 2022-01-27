#include "Model.h"


CModel::CModel(const std::string& InModelPath)
{
	ModelFilePath = InModelPath;
	Assimp::Importer ModelImporter;
	const aiScene* AssimpScene = ModelImporter.ReadFile(ModelFilePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (!AssimpScene || AssimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !AssimpScene->mRootNode)
	{
		std::cout << "Assimp error loading model:: " << ModelImporter.GetErrorString() << std::endl;
		return;
	}
	ProcessNode(AssimpScene->mRootNode, AssimpScene);
}

void CModel::Draw(CShaderProgram* Shader)
{
	// Draw all the meshes in the model
	for (unsigned int i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].Draw(Shader);
	}
}

void CModel::ProcessNode(aiNode* AssimpNode, const aiScene* AssimpScene)
{
	for (unsigned int i = 0; i < AssimpNode->mNumMeshes; i++)
	{
		aiMesh* AssimpMesh = AssimpScene->mMeshes[AssimpNode->mMeshes[i]];
		Meshes.push_back(ProcessMesh(AssimpMesh, AssimpScene));
	}
	
	// Process any children
	for (unsigned int i = 0; i < AssimpNode->mNumChildren; i++)
	{
		ProcessNode(AssimpNode->mChildren[i], AssimpScene);
	}
}

CMesh CModel::ProcessMesh(aiMesh* AssimpMesh, const aiScene* AssimpScene)
{
	std::vector<FVertex> Vertices;
	std::vector<unsigned int> Indices;

	// Collect all the vertices
	for (unsigned int i = 0; i < AssimpMesh->mNumVertices; i++)
	{
		FVertex Vertex;
		Vertex.Position = glm::vec3(AssimpMesh->mVertices[i].x, AssimpMesh->mVertices[i].y, AssimpMesh->mVertices[i].z);
		
		if (AssimpMesh->HasNormals())
		{
			Vertex.Normal = glm::vec3(AssimpMesh->mNormals[i].x, AssimpMesh->mNormals[i].y, AssimpMesh->mNormals[i].z);
		}

		if (AssimpMesh->mTextureCoords[0])
		{
			Vertex.TexCoords = glm::vec2(AssimpMesh->mTextureCoords[0][i].x, AssimpMesh->mTextureCoords[0][i].y);
		}
		else 
		{
			Vertex.TexCoords = glm::vec2(0.0f);
		}
		Vertices.push_back(Vertex);
	}

	// Process faces
	for (unsigned int i = 0; i < AssimpMesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < AssimpMesh->mFaces[i].mNumIndices; j++)
		{
			Indices.push_back(AssimpMesh->mFaces[i].mIndices[j]);
		}
	}

	// Process Textures

	aiMaterial* AssimpMaterial = AssimpScene->mMaterials[AssimpMesh->mMaterialIndex];
	std::vector<COpenGLTexture> Textures;
	FMaterial Material;

	if (AssimpMaterial->GetTextureCount(aiTextureType_DIFFUSE) != 0)
	{ 
		std::vector<COpenGLTexture> DiffuseMaps = LoadMaterialTextures(AssimpMaterial, aiTextureType_DIFFUSE, ETextureType::DIFFUSE);
		Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());
		Material.bShouldUseDiffuseTexture = true;
	}
	else
	{
		// No diffuse textures were found. This mesh would use the associated material instead
		aiColor4D AssimpColor;
		if (aiGetMaterialColor(AssimpMaterial, AI_MATKEY_COLOR_DIFFUSE, &AssimpColor) == AI_SUCCESS)
		{
			Material.DiffuseColor = glm::vec4(AssimpColor.r, AssimpColor.g, AssimpColor.b, AssimpColor.a);
			Material.bShouldUseDiffuseTexture = false;
		}
		else
		{
			// Set to use material texture so that it would load the failed texture.
			Material.bShouldUseDiffuseTexture = true;
		}
	}

	if (AssimpMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
	{
		std::vector<COpenGLTexture> SpecularMaps = LoadMaterialTextures(AssimpMaterial, aiTextureType_SPECULAR, ETextureType::SPECULAR);
		Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());
		Material.bShouldUseSpecularTexture = true;
	}
	else
	{
		// No diffuse textures were found. This mesh would use the associated material instead
		aiColor4D AssimpColor;
		if (aiGetMaterialColor(AssimpMaterial, AI_MATKEY_COLOR_SPECULAR, &AssimpColor) == AI_SUCCESS)
		{
			Material.SpecularColor = glm::vec4(AssimpColor.r, AssimpColor.g, AssimpColor.b, AssimpColor.a);
			Material.bShouldUseSpecularTexture = false;
		}
		else
		{
			// Set to use material texture so that it would load the failed texture.
			Material.bShouldUseSpecularTexture = true;
		}
	}
	if (aiGetMaterialFloat(AssimpMaterial, AI_MATKEY_SHININESS, &Material.Shininess) != AI_SUCCESS)
	{
		Material.Shininess = 0.0f;
	}
	if (aiGetMaterialFloat(AssimpMaterial, AI_MATKEY_SHININESS_STRENGTH, &Material.ShininessStrength) != AI_SUCCESS)
	{
		Material.Shininess = 1.0f;
	}
	return CMesh(Vertices, Indices, Textures, Material);

}

std::vector<COpenGLTexture> CModel::LoadMaterialTextures(aiMaterial* AssimpMaterial, aiTextureType AssimpTextureType, ETextureType TextureType)
{
	std::string Directory = ModelFilePath.substr(0, ModelFilePath.find_last_of('/'));
	std::vector<COpenGLTexture> Textures;
	for (unsigned int i = 0; i < AssimpMaterial->GetTextureCount(AssimpTextureType); i++)
	{
		aiString TexturePath;
		AssimpMaterial->GetTexture(AssimpTextureType, i, &TexturePath);
		std::string TexturePathString = std::string(TexturePath.C_Str());

		auto ExistingTextureIterator = LoadedTexturesMap.find(TexturePathString);
		// Create texture if it doest exist, else use existing one
		if (ExistingTextureIterator == LoadedTexturesMap.end())
		{
			// Create texture object to store the texture
			COpenGLTexture LoadedTexture(Directory + '/' + TexturePathString);
			LoadedTexture.TextureType = TextureType;
			LoadedTexturesMap.insert(std::pair<std::string, COpenGLTexture>(TexturePathString, LoadedTexture));
			Textures.push_back(LoadedTexture);
		}
		else
		{
			Textures.push_back(ExistingTextureIterator->second);
		}
	}
	return Textures;
}

