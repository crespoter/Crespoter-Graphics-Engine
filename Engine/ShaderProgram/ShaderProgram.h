#pragma  once
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "../Constants/ShaderConstants.h"



class CShaderProgram {
public:
	/**
	 * Initializes shader program with vertex, fragment and optional geometry shader
	 * @param VertexShaderFilePath(std::string): Relative path to the vertex shader
	 * @param FragmentShaderFilePath(std::string): Relative path to the fragment shader 
	 * @param GeometryShaderFilePath(std::string): Optional path to geometry shader. Passing null would compile without geometry shader.
	 */
	CShaderProgram(const std::string &VertexShaderFilePath, const std::string &FragmentShaderFilePath);

	/**
	* Initializes shader program from the predefined path definitions
	*/
	CShaderProgram(const FShaderPathDefinition ShaderPathDefinition);
	
	/**
	* Initializes shader with the default shader
	*/
	CShaderProgram();

	
	/**
	 * Activates the shader program
	 */
	void Activate();
	
	/**
	 * Sets a uniform bool variable
	 * @param VariableName(std::string): Name of the uniform variable in the shader file
	 * @param Value(bool): Value to set
	 */
	void SetBool(const std::string &VariableName, bool Value) const;

	/**
	 * Sets a uniform int variable
	 * @param VariableName(std::string): Name of the uniform variable in the shader file
	 * @param Value(int): Value to set
	 */
	void SetInteger(const std::string& VariableName, int Value) const;

	/**
	 * Sets a uniform int variable
	 * @param VariableName(std::string): Name of the uniform variable in the shader file
	 * @param Value(float): Value to set
	 */
	void SetFloat(const std::string& VariableName, float Value) const;

	/**
	 * Sets a uniform mat4 variable
	 * @param VariableName(std::string): Name of the uniform variable in the shader file
	 * @param Value(std::mat4): Value to set
	 */
	 void SetMat4(const std::string& VariableName, glm::mat4 Value) const;

	 /**
	  * Sets a uniform vec3 variable
	  * @param VariableName(std::string): Name of the uniform variable in the shader file
	  * @param Value(std::vec3): Value to set
	  */
	 void SetVec3(const std::string& VariableName, glm::vec3 Value) const;

	 /**
	  * Sets a uniform vec4 variable
	  * @param VariableName(std::string): Name of the uniform variable in the shader file
	  * @param Value(std::vec4): Value to set
	  */
	 void SetVec4(const std::string& VariableName, glm::vec4 Value) const;

private:
	unsigned int ProgramID = 0;

	/**
	 * Helper function to read from a file
	 * @param FilePath(std::string) Path to file
	 */
	std::string ReadFromFile(const std::string& FilePath);

	/**
	 * Compiles a shader file and returns shader id
	 * @param ShaderType(unsigned int): Type of shader from the glad.h library.
	 */
	 unsigned int CompileShader(unsigned int ShaderType, const char* SourceCode);

	 /**
	 * Initializes ShaderProgram with the provided shader paths.
	 */
	 void Initialize(const std::string &VertexShaderPath, const std::string &FragmentShaderPath);
};