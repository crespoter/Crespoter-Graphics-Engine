#version 330 core

struct FMaterial
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};

struct FLight
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

out vec4 FragColor;
in vec2 texCoords;
in vec3 Normal;
in vec3 FragPos;

uniform FMaterial Material;
uniform FLight Light;

uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 ViewPosition;

void main()
{
	// Ambient component calculation
	vec3 AmbientComponent = Light.Ambient * Material.Ambient;
	
	// Diffuse component calculation
	vec3 Norm =normalize(Normal);
	vec3 LightDirection = normalize(LightPos - FragPos);
	vec3 DiffuseComponent = Light.Diffuse * (max(dot(Norm, LightDirection), 0.0) * Material.Diffuse);

    // Specular component calculation
    vec3 ViewDirection = normalize(ViewPosition - FragPos);
    vec3 ReflectDirection = reflect(-LightDirection, Norm);  
    float Spec = pow(max(dot(ViewDirection, ReflectDirection), 0.0), Material.Shininess);
    vec3 SpecularComponent = Light.Specular * (Spec * Material.Specular);  
	
	

	FragColor =  vec4((AmbientComponent + DiffuseComponent + SpecularComponent) * mix (texture(Texture, texCoords), texture(Texture2, texCoords), 0.5).xyz, 1.0);
	
}
