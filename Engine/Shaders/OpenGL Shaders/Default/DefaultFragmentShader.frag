#version 330 core

struct FMaterial
{
	sampler2D Diffuse0;
	sampler2D Specular0;
	float Shininess;
	float ShininessStrength;
	bool bShouldUseDiffuseTexture;
	bool bShouldUseSpecularTexture;
	vec3 AmbientColor;
	vec3 DiffuseColor;
	vec3 SpecularColor;
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
	vec3 AmbientColor = Material.AmbientColor;
	vec3 DiffuseColor = Material.DiffuseColor;
	
	// Ambient component calculation

	if (Material.bShouldUseDiffuseTexture)
	{
		AmbientColor = vec3(texture(Material.Diffuse0, TexCoords));
		DiffuseColor = AmbientColor;
	}
	vec3 AmbientComponent = Light.Ambient * AmbientColor;
	
	// Diffuse component calculation



	vec3 Norm =normalize(Normal);
	vec3 LightDirection = normalize(LightPos - FragPos);
	vec3 DiffuseComponent = Light.Diffuse * (max(dot(Norm, LightDirection), 0.0) * DiffuseColor);

    // Specular component calculation
    vec3 ViewDirection = normalize(ViewPosition - FragPos);
    vec3 ReflectDirection = reflect(-LightDirection, Norm);  
	float Spec;
	if (Material.Shininess < 0.5f) // Handle float rounding error
	{
		Spec = 0.0;
	}
	else
	{
		Spec = pow(max(dot(ViewDirection, ReflectDirection), 0.0),  Material.Shininess < 0.05 ? 0.0 : Material.Shininess);
	}


	vec3 SpecularColor = Material.SpecularColor;
	if (Material.bShouldUseSpecularTexture)
	{
		SpecularColor = vec3(texture(Material.Specular0, TexCoords));
	}

    vec3 SpecularComponent = Material.ShininessStrength * Light.Specular * (Spec * SpecularColor);  

	FragColor =  vec4(AmbientComponent + DiffuseComponent + SpecularComponent, 1.0);
	
}
