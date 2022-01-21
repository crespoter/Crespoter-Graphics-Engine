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

class CMesh
{
public:
	CMesh(const std::vector<FVertex> &Vertices, const std::vector<unsigned int> &Indices, std::vector<COpenGLTexture> Textures);
	void Draw(CShaderProgram* ShaderProgram);
private:
	unsigned int VertexArrayObject = 0;
	unsigned int VertexBufferObject = 0;
	unsigned int ElementBufferObject = 0;
	unsigned int IndexCount = 0;
	std::vector<COpenGLTexture> Textures;
	std::vector<unsigned int> Indices;
	std::vector<FVertex> Vertices; 
};