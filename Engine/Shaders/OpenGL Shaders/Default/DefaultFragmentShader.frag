#version 330 core

#define MAX_POINT_LIGHTS 10

struct FMaterial
{
	sampler2D Diffuse0;
	sampler2D Specular0;
	float Shininess;
	float ShininessStrength;
	bool bShouldUseDiffuseTexture;
	bool bShouldUseSpecularTexture;
	vec4 AmbientColor;
	vec4 DiffuseColor;
	vec4 SpecularColor;
};

struct FAttenuation
{
	float ConstantCoeff;
	float LinearCoeff;
	float QuadraticCoeff;
};

struct FPointLight
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Position;
	vec3 LightPos;
	FAttenuation Attenuation;
};

struct FDirectionalLight
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	vec3 Direction;
	bool bIsActive;
};

out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform FMaterial Material;
uniform FDirectionalLight DirectionalLight;
uniform FPointLight PointLights[MAX_POINT_LIGHTS];
uniform int PointLightCount;

uniform vec3 ViewPosition;


vec3 NormalizedNormal;
vec3 AmbientColor;
vec3 DiffuseColor;
vec3 SpecularColor;

vec3 CalculatePointLight(int Index)
{
	
	vec3 AmbientComponent = PointLights[Index].Ambient * AmbientColor;
	
	// Diffuse component calculation
	vec3 LightDirection = normalize(PointLights[Index].LightPos - FragPos);
	vec3 DiffuseComponent = PointLights[Index].Diffuse * max(dot(NormalizedNormal, LightDirection), 0.0) * DiffuseColor;

    // Specular component calculation
    vec3 ViewDirection = normalize(ViewPosition - FragPos);
    vec3 ReflectDirection = reflect(-LightDirection, NormalizedNormal);  
	float Spec;
	vec3 HalfwayDirection = normalize(LightDirection + ViewDirection);

	Spec = pow(max(dot(HalfwayDirection, NormalizedNormal), 0.0),  Material.Shininess < 0.05 ? 0.0 : Material.Shininess);


    vec3 SpecularComponent = Material.ShininessStrength * PointLights[Index].Specular * (Spec * SpecularColor);

	// Attenuation calculations
	float Distance = length(PointLights[Index].LightPos - FragPos);
	float Attenuation = 1.0 / (PointLights[Index].Attenuation.ConstantCoeff + Distance * PointLights[Index].Attenuation.LinearCoeff + (Distance * Distance) * PointLights[Index].Attenuation.QuadraticCoeff);

	return (AmbientComponent + DiffuseComponent + SpecularComponent) * Attenuation;
}

vec3 CalculateDirectionalLight()
{
	if (!DirectionalLight.bIsActive)
	{
		return vec3(0.0, 0.0, 0.0);
	}

	vec3 AmbientComponent = DirectionalLight.Ambient * AmbientColor;

	vec3 LightDirection = normalize(-DirectionalLight.Direction);
    vec3 DiffuseComponent = max(dot(NormalizedNormal, LightDirection), 0.0) * DirectionalLight.Diffuse * DiffuseColor;
   
	vec3 ReflectDirection = reflect(-LightDirection, Normal);
	vec3 ViewDirection = normalize(ViewPosition - FragPos);

	vec3 HalfwayDirection = normalize(LightDirection + ViewDirection);

	float Spec;

	Spec = pow(max(dot(NormalizedNormal, HalfwayDirection), 0.0),  Material.Shininess < 0.05 ? 0.0 : Material.Shininess);	

	vec3 SpecularComponent = Material.ShininessStrength *DirectionalLight.Specular * (Spec * SpecularColor);

    return (AmbientComponent + DiffuseComponent + SpecularComponent);
}


void main()
{
	NormalizedNormal =normalize(Normal);

	AmbientColor = Material.AmbientColor.xyz;
	DiffuseColor = Material.DiffuseColor.xyz;	

	if (Material.bShouldUseDiffuseTexture)
	{
		AmbientColor = vec3(texture(Material.Diffuse0, TexCoords));
		DiffuseColor = AmbientColor;
	}
	
	SpecularColor = Material.SpecularColor.xyz;

	if (Material.bShouldUseSpecularTexture)
	{
		SpecularColor = vec3(texture(Material.Specular0, TexCoords));
	}
	else
	{
		// Multiply by the diffuse color as there is no texture;
		SpecularColor = SpecularColor * Material.DiffuseColor.xyz;
	}
	vec3 FinalResult = vec3(0.0);

	// Calculate point lights
	for (int i = 0; i < PointLightCount; i++)
	{
		FinalResult += CalculatePointLight(i);		
	}

	// Directional Light
	FinalResult += CalculateDirectionalLight();


	FragColor =  vec4(FinalResult, 1.0);
}



