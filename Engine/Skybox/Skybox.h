#pragma once

#include <string>
#include <vector>
#include "../ShaderProgram/ShaderProgram.h"

class CSkybox
{
public:
	CSkybox(const std::string& TextureRootLocation);
	~CSkybox();
	void Draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);
private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int TextureID = 0;
	CShaderProgram* SkyShader;
};