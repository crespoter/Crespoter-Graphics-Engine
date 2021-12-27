#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	gl_Position =  ProjectionMatrix * ViewMatrix *  ModelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	texCoords = aTexCoords;
}