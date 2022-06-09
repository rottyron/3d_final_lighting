#include "CLightManager.h"

CLightManager::CLightManager()
{
	pointLights[0].position = glm::vec3(-4.0f, 6.0f, 0.0f);
	pointLights[0].color = glm::vec3(0.0f, 0.5f, 0.7f);
	pointLights[0].ambientStrength = 0.03f;
	pointLights[0].specularStrength = 1.0f;
	pointLights[0].attenuationConstant = 1.0f;
	pointLights[0].attenuationLinear = 0.045f;
	pointLights[0].attenuationExponent = 0.0075f;


	pointLights[1].position = glm::vec3(4.0f, -6.0f, 0.0f);
	pointLights[1].color = glm::vec3(1.0f, 0.0f, 0.0f);
	pointLights[1].ambientStrength = 0.03f;
	pointLights[1].specularStrength = 1.0f;
	pointLights[1].attenuationConstant = 1.0f;
	pointLights[1].attenuationLinear = 0.022f;
	pointLights[1].attenuationExponent = 0.0019f;

	directLight.direction = glm::vec3(-1.0f, -1.0f, 0.0f);
	directLight.color = glm::vec3(0.3f, 0.3f, 0.3f);
	directLight.ambientStrength = 0.02f;
	directLight.specularStrength = 1.0f;
}

CLightManager::~CLightManager()
{
}

void CLightManager::Update(float _deltaTime)
{

}

void CLightManager::PassLights(GLuint* _program)
{
	
	//blue
	glUniform3fv(glGetUniformLocation(*_program, "pointLights[0].position"), 1, glm::value_ptr(pointLights[0].position));
	glUniform3fv(glGetUniformLocation(*_program, "pointLights[0].color"), 1, glm::value_ptr(pointLights[0].color));
	glUniform1f(glGetUniformLocation(*_program, "pointLights[0].ambientStrength"), pointLights[0].ambientStrength);
	glUniform1f(glGetUniformLocation(*_program, "pointLights[0].specularStrength"), pointLights[0].specularStrength);

	glUniform1f(glGetUniformLocation(*_program, "pointLights[0].attenuationConstant"), pointLights[0].attenuationConstant);
	glUniform1f(glGetUniformLocation(*_program, "pointLights[0].attenuationLinear"), pointLights[0].attenuationLinear);
	glUniform1f(glGetUniformLocation(*_program, "pointLights[0].attenuationExponent"), pointLights[0].attenuationExponent);

	//red
	glUniform3fv(glGetUniformLocation(*_program, "pointLights[1].position"), 1, glm::value_ptr(pointLights[1].position));
	glUniform3fv(glGetUniformLocation(*_program, "pointLights[1].color"), 1, glm::value_ptr(pointLights[1].color));
	glUniform1f(glGetUniformLocation(*_program, "pointLights[1].ambientStrength"), pointLights[1].ambientStrength);
	glUniform1f(glGetUniformLocation(*_program, "pointLights[1].specularStrength"), pointLights[1].specularStrength);

	glUniform1f(glGetUniformLocation(*_program, "pointLights[1].attenuationConstant"), pointLights[1].attenuationConstant);
	glUniform1f(glGetUniformLocation(*_program, "pointLights[1].attenuationLinear"), pointLights[1].attenuationLinear);
	glUniform1f(glGetUniformLocation(*_program, "pointLights[1].attenuationExponent"), pointLights[1].attenuationExponent);

	//directionalLight
	glUniform3fv(glGetUniformLocation(*_program, "directLight.direction"), 1, glm::value_ptr(directLight.direction));
	glUniform3fv(glGetUniformLocation(*_program, "directLight.color"), 1, glm::value_ptr(directLight.color));
	glUniform1f(glGetUniformLocation(*_program, "directLight.ambientStrength"), directLight.ambientStrength);
	glUniform1f(glGetUniformLocation(*_program, "directLight.specularStrength"), directLight.specularStrength);




}
