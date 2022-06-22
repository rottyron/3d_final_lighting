//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : 3dLight_BlinnPhone.fs
// Description : fragment shader that handles most of the orbs lighting, all the generic ones
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#version 460 core
#define MAX_POINT_LIGHTS 4

struct pointLight
{
	vec3 position;
	vec3 color;
	float ambientStrength;
	float specularStrength;

	float attenuationConstant;
	float attenuationLinear;
	float attenuationExponent;
};
	
struct directionalLight	
{
	vec3 direction;
	vec3 color;
	float ambientStrength;
	float specularStrength;
};

//Vertex Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

//uniform inputs
uniform sampler2D ImageTexture0;
uniform pointLight pointLights[MAX_POINT_LIGHTS];
uniform directionalLight directLight;
uniform vec3 CameraPos;
uniform vec3 AmbientColor				= vec3(1.0f,1.0f,1.0f);
uniform float Shininess					= 16.0f;

//output
out vec4 FinalColor;

//Looped function to calculate the individual lights
vec3 CalculateLight_Point(pointLight _light)
{
	// Light direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - _light.position);

	//ambient Component
	vec3 Ambient = _light.ambientStrength * AmbientColor;

	//Diffuse Componenet
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * _light.color;
	
	//Specula stuff
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);

	//Calculate and apply attenuation
	float distance = length(_light.position - FragPos);
	float attenuation = _light.attenuationConstant + (_light.attenuationLinear * distance) + (_light.attenuationExponent * pow(distance, 2));
	
	
	//Calculate the final specular component
	vec3 Specular = _light.specularStrength * SpecularReflectivity * _light.color;

	//combine the lighting components
	vec3 combinedLight = Ambient + Diffuse + Specular;
	combinedLight /= attenuation;

	return combinedLight;
}

vec3 CalculateDirectionalLight(directionalLight _light)
{
	//Ambient diffuse and specular are the same as above
	// Light direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - _light.direction);

	//ambient Component
	vec3 Ambient = _light.ambientStrength * AmbientColor;

	//Diffuse Componenet
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * _light.color;
	
	//Specula stuff
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);

	//Blin phong model
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
	
	//Calculate the final specular component
	vec3 Specular = _light.specularStrength * SpecularReflectivity * _light.color;
	
	//combine the lighting components
	vec3 combinedLight = Ambient + Diffuse + Specular;

	return combinedLight;
}

//Main
void main()
{
	//calc the lights then output a final
	vec3 LightOutput = vec3(0.0f,0.0f,0.0f);
	for(int i = 0; i < 2; i++)				//For loop, loops through all the PointLights and adds them together
	{
		if(pointLights[i].attenuationConstant != 0.0f)
		{
			LightOutput += CalculateLight_Point(pointLights[i]);
		}
	}
	//Calc the directional light
	LightOutput += CalculateDirectionalLight(directLight);

	FinalColor = vec4(LightOutput, 1.0f) * texture(ImageTexture0, FragTexCoords);
}