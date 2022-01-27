#include "Mesh.h"
#include <glad/glad.h>
#include <stddef.h>
#include <assert.h>
#include <string>
#include "../../ShaderProgram/ShaderProgram.h"




CMesh::CMesh(const std::vector<FVertex> &InVertices, const std::vector<unsigned int> &InIndices, const std::vector<COpenGLTexture> &InTextures, const FMaterial &InMaterial)
{
	Vertices = InVertices;
	Indices = InIndices;
	IndexCount = Indices.size();
	Textures = InTextures;
	MeshMaterial = InMaterial;
	
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
		switch (Textures[i].TextureType)
		{
			case ETextureType::DIFFUSE:
				"Material.Diffuse" + std::to_string(DiffuseCount++);
				Textures[i].BindTexture(ShaderProgram, "Material.Diffuse", i);
				break;
			case ETextureType::SPECULAR:
				"Material.Specular" + std::to_string(SpecularCount++);
				Textures[i].BindTexture(ShaderProgram, "Material.Specular", i);
				break;
		}

	}
	// Set Uniforms
	ShaderProgram->SetFloat("Material.Shininess", MeshMaterial.Shininess);
	ShaderProgram->SetFloat("Material.ShininessStrength", MeshMaterial.ShininessStrength);
	ShaderProgram->SetBool("Material.bShouldUseDiffuseTexture", MeshMaterial.bShouldUseDiffuseTexture);
	ShaderProgram->SetBool("Material.bShouldUseSpecularTexture", MeshMaterial.bShouldUseSpecularTexture);
	ShaderProgram->SetVec3("Material.AmbientColor", MeshMaterial.AmbientColor);
	ShaderProgram->SetVec3("Material.DiffuseColor", MeshMaterial.DiffuseColor);
	ShaderProgram->SetVec3("Material.SpecularColor", MeshMaterial.SpecularColor);
	
	// Draw Mesh
	glBindVertexArray(VertexArrayObject);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
	
	// Reset binds
	glActiveTexture(0);
	glBindVertexArray(0);
}

