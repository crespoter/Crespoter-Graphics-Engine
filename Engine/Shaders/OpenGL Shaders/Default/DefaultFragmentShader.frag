#version 330 core
out vec4 FragColor;
in vec2 texCoords;
uniform sampler2D Texture;
uniform sampler2D Texture2;
void main()
{
	FragColor =  mix (texture(Texture, texCoords), texture(Texture2, texCoords), 0.5);
}
