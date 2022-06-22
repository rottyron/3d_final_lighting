//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CLightManager.cpp
// Description : Handles all of the lighting in the project
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#include "CLightManager.h"

//Initialiser
CLightManager::CLightManager()
{
	lightCount[0] = "pointLights[0]";
	//Pointlights 0 intiialize
	pointLights[0].position = glm::vec3(-4.0f, 6.0f, 0.0f);
	pointLights[0].color = glm::vec3(0.0f, 0.5f, 0.7f);
	pointLights[0].ambientStrength = 0.03f;
	pointLights[0].specularStrength = 1.0f;
	pointLights[0].attenuationConstant = 1.0f;
	pointLights[0].attenuationLinear = 0.045f;
	pointLights[0].attenuationExponent = 0.0075f;

	lightCount[1] = "pointLights[1]";
	//Pointlights 1 initialize
	pointLights[1].position = glm::vec3(4.0f, -6.0f, 0.0f);
	pointLights[1].color = glm::vec3(1.0f, 0.0f, 0.0f);
	pointLights[1].ambientStrength = 0.03f;
	pointLights[1].specularStrength = 1.0f;
	pointLights[1].attenuationConstant = 1.0f;
	pointLights[1].attenuationLinear = 0.022f;
	pointLights[1].attenuationExponent = 0.0019f;

	//Direction initialize
	directLight.direction = glm::vec3(-1.0f, -1.0f, 0.0f);
	directLight.color = glm::vec3(0.3f, 0.3f, 0.3f);
	directLight.ambientStrength = 0.02f;
	directLight.specularStrength = 1.0f;

	//Rim initialize
	rim.position = glm::vec3(-2.0f, 6.0f, 3.0f);
	rim.ambientStrength = 0.2f;
	rim.color = glm::vec3(1.0f);
	rim.rimColor = glm::vec3(1.0f, 0.f, 0.f);
	rim.specularStrength = 1.0f;

}
//destructor
CLightManager::~CLightManager()
{
}
//Update function for any required updates
void CLightManager::Update(float _deltaTime)
{

}

//Passes lights to the shader
void CLightManager::PassLights(GLuint* _program)
{
	std::string temp;
	//For loop to iterate through the point lights make sure they exist and then pass through the light info
	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		if (pointLights[i].position != glm::vec3(NULL))
		{
			temp.clear();
			temp = lightCount[i] + ".position";
			//blue
			glUniform3fv(glGetUniformLocation(*_program, temp.c_str()), 1, glm::value_ptr(pointLights[i].position));
			temp.clear();
			temp = lightCount[i] + ".color";
			glUniform3fv(glGetUniformLocation(*_program, temp.c_str()), 1, glm::value_ptr(pointLights[i].color));
			temp.clear();
			temp = lightCount[i] + ".ambientStrength";
			glUniform1f(glGetUniformLocation(*_program, temp.c_str()), pointLights[i].ambientStrength);
			temp.clear();
			temp = lightCount[i] + ".specularStrength";
			glUniform1f(glGetUniformLocation(*_program, temp.c_str()), pointLights[i].specularStrength);
			temp.clear();
			temp = lightCount[i] + ".attenuationConstant";
			glUniform1f(glGetUniformLocation(*_program, temp.c_str()), pointLights[i].attenuationConstant);
			temp.clear();
			temp = lightCount[i] + ".attenuationLinear";
			glUniform1f(glGetUniformLocation(*_program, temp.c_str()), pointLights[i].attenuationLinear);
			temp.clear();
			temp = lightCount[i] + ".attenuationExponent";
			glUniform1f(glGetUniformLocation(*_program, temp.c_str()), pointLights[i].attenuationExponent);
			temp.clear();
		}
	}

	//directionalLight
	glUniform3fv(glGetUniformLocation(*_program, "directLight.direction"), 1, glm::value_ptr(directLight.direction));
	glUniform3fv(glGetUniformLocation(*_program, "directLight.color"), 1, glm::value_ptr(directLight.color));
	glUniform1f(glGetUniformLocation(*_program, "directLight.ambientStrength"), directLight.ambientStrength);
	glUniform1f(glGetUniformLocation(*_program, "directLight.specularStrength"), directLight.specularStrength);




}

//Only does the rim lights
void CLightManager::PassRimLights(GLuint* _program)
{
	//vector3s
	glUniform3fv(glGetUniformLocation(*_program, "rim.Position"), 1, glm::value_ptr(rim.position));
	glUniform3fv(glGetUniformLocation(*_program, "rim.Color"), 1, glm::value_ptr(rim.color));
	glUniform3fv(glGetUniformLocation(*_program, "rim.RimColor"), 1, glm::value_ptr(rim.rimColor));

	//floats
	glUniform1f(glGetUniformLocation(*_program, "rim.RimExponent"), rim.rimExponent);
	glUniform1f(glGetUniformLocation(*_program, "rim.AmbientStrength"), rim.ambientStrength);
	glUniform1f(glGetUniformLocation(*_program, "rim.SpecularStrength"), rim.specularStrength);
}
