//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : 3dLight_BlinnPhongRim.fs
// Description : Calcs the blinnPhong lighting and the rim lighting
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#version 460 core

//Vertex Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

//uniform inputs
uniform sampler2D ImageTexture0;
uniform vec3 CameraPos;

//RimLight struct holds all the rimlight stuff
struct rimLight
{
	float AmbientStrength;
	vec3 Color;
	vec3 Pos;

	float RimExponent;
	vec3 RimColor;
	float SpecularStrength;
};

uniform rimLight rim;
uniform vec3 AmbientColor				= vec3(1.0f,1.0f,1.0f);
uniform float Shininess					= 16.0f;

//rim color
uniform float RimExponent = 4.0f;
uniform vec3 RimColor = vec3(1.0f, 0.0f, 0.0f);

//output
out vec4 FinalColor;

//Calculates the rim light reqs
vec3 calculateRim(rimLight _light)
{
	// Light direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - _light.Pos);

	//ambient Component
	vec3 Ambient = _light.AmbientStrength * AmbientColor;

	//Diffuse Componenet
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * _light.Color;
	
	//Specular stuff
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);

	//Blin phong model
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);

	//Rim component
	float RimFactor = 1.0f - dot(FragNormal, ReverseViewDir);
	RimFactor = smoothstep(0.0f,1.0f,RimFactor);
	RimFactor = pow(RimFactor, _light.RimExponent);
	vec3 Rim = RimFactor * _light.RimColor * _light.Color;
	
	vec3 Specular = _light.SpecularStrength * SpecularReflectivity * _light.Color;

	//combine the lighting components
	vec3 combinedLight = Ambient + Diffuse + Specular + Rim;
	
	//calculate the final color
	return combinedLight;
}

void main()
{	
	vec3 finalLight = calculateRim(rim);
	//calculate the final color
	FinalColor = vec4(finalLight,1.0f) * texture(ImageTexture0, FragTexCoords);
}