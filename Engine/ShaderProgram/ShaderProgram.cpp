#include "ShaderProgram.h"
#include <fstream>
#include <string>
#include <glad/glad.h>

CShaderProgram::CShaderProgram(const std::string& VertexShaderFilePath, const std::string& FragmentShaderFilePath)
{
	// Read shader files
	std::string VertexShaderCode = ReadFromFile(VertexShaderFilePath);
	std::string FragmentShaderCode = ReadFromFile(FragmentShaderFilePath);
	// Compile shaders
	unsigned int VertexShaderID = CompileShader(GL_VERTEX_SHADER, VertexShaderCode.c_str());
	unsigned int FragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, FragmentShaderCode.c_str());
	// Create program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	// Print any linking errors
	int Success;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Success);
	if (!Success)
	{
		char InfoLog[512];
		glGetProgramInfoLog(ProgramID, 512, NULL, InfoLog);
		std::cout << "Error occurred while linking program\n" << InfoLog << std::endl; 
	}
	// Delete shaders since they are linked now
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}

void CShaderProgram::Activate()
{
	glUseProgram(ProgramID);
}

void CShaderProgram::SetBool(const std::string& VariableName, bool Value) const
{
	glUniform1i(glGetUniformLocation(ProgramID, VariableName.c_str()), (int)Value);
}

void CShaderProgram::SetInteger(const std::string& VariableName, int Value) const
{
	glUniform1i(glGetUniformLocation(ProgramID, VariableName.c_str()), Value);
}

void CShaderProgram::SetFloat(const std::string& VariableName, float Value) const
{
	glUniform1f(glGetUniformLocation(ProgramID, VariableName.c_str()), Value);
}

void CShaderProgram::SetMat4(const std::string& VariableName, glm::mat4 Value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, VariableName.c_str()), 1, GL_FALSE, glm::value_ptr(Value));
}

std::string CShaderProgram::ReadFromFile(const std::string& FilePath)
{
	std::string FileString = "";
	std::ifstream FileToRead(FilePath);
	if (FileToRead.fail())
	{
		std::cout << "Unable to read file : " << FilePath;
		return "";
	}
	std::string Line;
	while (getline(FileToRead, Line))
	{
		FileString += (Line + "\n");
	}
	return FileString;

}

unsigned int CShaderProgram::CompileShader(unsigned int ShaderType, const char* SourceCode)
{
	unsigned int ShaderID = glCreateShader(ShaderType);
	glShaderSource(ShaderID, 1, &SourceCode, NULL);
	glCompileShader(ShaderID);

	// Log errors if any
	char InfoLog[512];
	int Success;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(ShaderID, 512, NULL, InfoLog);
		std::cout << "Error occurred compiling shader" << InfoLog << std::endl;
	}
	return ShaderID;
}
