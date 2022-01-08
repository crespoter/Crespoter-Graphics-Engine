#version 330 core
out vec4 FragColor;
in vec2 texCoords;
in vec3 normal;
in vec3 FragPos;
uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;


void main()
{
	float ambientStrength = 0.1;
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(lightPos - FragPos);
	
	vec3 ambientLight = ambientStrength * lightColor;
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDirection, norm);  
	float specularStrength = 2.0;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	vec3 specular = specularStrength * spec * lightColor;  


	FragColor =  vec4((ambientLight + diffuse + specular) * mix (texture(Texture, texCoords), texture(Texture2, texCoords), 0.5).xyz, 1.0);
}
