//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name :3dReflect.fs 
// Description : This is the reflection shader, and handles the reflections on the object
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
uniform samplerCube ImageTexture1;
uniform vec3 CameraPos;
uniform float AmbientStrength			= 0.5f;
uniform vec3 AmbientColor				= vec3(1.0f,1.0f,1.0f);
uniform vec3 LightColor					= vec3(1.0f,1.0f,1.0f);
uniform vec3 LightPos					= vec3(-2.0f, 6.0f, 3.0f);
uniform float LightSpecularStrength		= 1.0f;
uniform float Shininess					= 16.0f;

//output
out vec4 FinalColor;

void main()
{
	// Light direction
	vec3 Normal = normalize(FragNormal);
	
	//reflectin things
	vec3 viewDir = normalize(FragPos - CameraPos);
	vec3 ReflectDir = reflect(viewDir, Normal);

	vec3 LightDir = normalize(CameraPos - FragPos); //Look from here

	//ambient Component
	vec3 Ambient = AmbientStrength * AmbientColor;

	//Diffuse Componenet
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * LightColor;
	
	//Specular stuff
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);

	//Blin phong model
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);

	vec3 Specular = LightSpecularStrength * SpecularReflectivity * LightColor;

	//combine the lighting components
	vec4 Light = vec4(Ambient + Diffuse + Specular, 1.0f);
	
	//calculate the final color
	FinalColor = Light * mix(texture(ImageTexture0, FragTexCoords), texture(ImageTexture1, ReflectDir), 1.0f);
}