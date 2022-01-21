#version 330 core

struct FMaterial
{
	sampler2D Diffuse0;
	sampler2D Specular0;
	float Shininess;
};

struct FLight
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform FMaterial Material;
uniform FLight Light;

uniform vec3 LightPos;
uniform vec3 ViewPosition;

void main()
{
	// Ambient component calculation
	vec3 AmbientComponent = Light.Ambient * vec3(texture(Material.Diffuse0, TexCoords));
	
	// Diffuse component calculation
	vec3 Norm =normalize(Normal);
	vec3 LightDirection = normalize(LightPos - FragPos);
	vec3 DiffuseComponent = Light.Diffuse * (max(dot(Norm, LightDirection), 0.0) * vec3(texture(Material.Diffuse0, TexCoords)));

    // Specular component calculation
    vec3 ViewDirection = normalize(ViewPosition - FragPos);
    vec3 ReflectDirection = reflect(-LightDirection, Norm);  
    float Spec = pow(max(dot(ViewDirection, ReflectDirection), 0.0), Material.Shininess);
    vec3 SpecularComponent = Light.Specular * (Spec * vec3(texture(Material.Specular0, TexCoords)));  

	FragColor =  vec4(AmbientComponent + DiffuseComponent + SpecularComponent, 1.0);
	
}
