#include "Mesh.h"
#include <glad/glad.h>
#include <stddef.h>
#include <assert.h>
#include <string>




CMesh::CMesh(const std::vector<FVertex> &InVertices, const std::vector<unsigned int> &InIndices, std::vector<COpenGLTexture> InTextures)
{
	Vertices = InVertices;
	Indices = InIndices;
	IndexCount = Indices.size();
	Textures = InTextures;
	
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);

	// Create vertex
	glBindVertexArray(VertexArrayObject);	
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertices), &Vertices[0], GL_STATIC_DRAW);

	// Handle indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

	//Setup vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)offsetof(FVertex, TexCoords));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)offsetof(FVertex, Normal));
	glEnableVertexAttribArray(2);


	// Unbind
	glBindVertexArray(0);
}



void CMesh::Draw(CShaderProgram* ShaderProgram)
{
	unsigned int DiffuseCount = 0;
	unsigned int SpecularCount = 0;

	assert(Textures.size() <= 16);
	
	// Bind textures
	for (unsigned int i = 0; i < Textures.size(); i++)
	{
		std::string UniformName = "Material";
		switch (Textures[i].TextureType)
		{
			case ETextureType::DIFFUSE:
				UniformName +=  ".Diffuse" + std::to_string(DiffuseCount++);
				break;
			case ETextureType::SPECULAR:
				UniformName +=  ".Specular" + std::to_string(SpecularCount++);
				break;
		}

		Textures[i].BindTexture(ShaderProgram, UniformName ,i);
	}
	// Draw Mesh
	glBindVertexArray(VertexArrayObject);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
	
	// Reset binds
	glActiveTexture(0);
	glBindVertexArray(0);
}

