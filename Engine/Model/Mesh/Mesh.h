#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "../../Texture/OpenGLTexture/OpenGLTexture.h"

struct FVertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct FMaterial
{
	glm::vec4 DiffuseColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 SpecularColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 AmbientColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	bool bShouldUseDiffuseTexture = false;
	bool bShouldUseSpecularTexture = false;
	float Shininess = 0.0f;
	float ShininessStrength = 1.0f;
};

class CMesh
{
public:
	CMesh(const std::vector<FVertex> &InVertices, const std::vector<unsigned int> &InIndices, const std::vector<COpenGLTexture> &InTextures, const FMaterial &InMaterial);
	void Draw(CShaderProgram* ShaderProgram);
private:
	unsigned int VertexArrayObject = 0;
	unsigned int VertexBufferObject = 0;
	unsigned int ElementBufferObject = 0;
	unsigned int IndexCount = 0;
	std::vector<COpenGLTexture> Textures;
	std::vector<unsigned int> Indices;
	std::vector<FVertex> Vertices; 
	FMaterial MeshMaterial;
};