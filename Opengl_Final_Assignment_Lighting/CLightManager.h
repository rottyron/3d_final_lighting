//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CLightManager.h
// Description : Light manager header file
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#pragma once
#include "includeStorage.h"
class CLightManager
{
public:
	//Initializer
	CLightManager();
	//Destructor
	~CLightManager();
	//General update function
	void Update(float _deltaTime);
	//Pass the lights to the shader
	void PassLights(GLuint* _program);
	//pass the lights for the rimLighting
	void PassRimLights(GLuint* _program);
private:
	//struct for pointLight
	struct pointLight
	{
		glm::vec3 position;
		glm::vec3 color;
		float ambientStrength;
		float specularStrength;

		float attenuationConstant;
		float attenuationLinear;
		float attenuationExponent;
	};
	//struct for directional lights
	struct directionalLight
	{
		glm::vec3 direction;
		glm::vec3 color;
		float ambientStrength;
		float specularStrength;
	};
	struct rimLight
	{
		glm::vec3 position;
		glm::vec3 color;
		float ambientStrength;
		float specularStrength;

		//rim stuff
		float rimExponent = 4.0f;
		glm::vec3 rimColor = glm::vec3(1.0f, 0.0f, 0.0f);
	};

	//Struct objects and int to clamp the amount of lights
	static const int MAX_POINT_LIGHTS = 4;
	pointLight pointLights[MAX_POINT_LIGHTS];
	directionalLight directLight;
	rimLight rim;

	//string vector to hold info on multiple point lights
	std::string lightCount[4];

};

