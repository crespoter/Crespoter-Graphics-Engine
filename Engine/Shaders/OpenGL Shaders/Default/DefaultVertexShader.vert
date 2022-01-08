#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 texCoords;
out vec3 normal;
out vec3 FragPos;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	gl_Position =  ProjectionMatrix * ViewMatrix *  ModelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	FragPos = vec3(ModelMatrix * vec4(aPos, 1.0));

	texCoords = aTexCoords;
	// TODO: Do not do inverse in shader
	normal = mat3(transpose(inverse(ModelMatrix))) * aNormal;
}