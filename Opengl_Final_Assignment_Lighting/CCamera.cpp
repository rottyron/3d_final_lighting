#include "CCamera.h"

CCamera::CCamera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	cameraLookDir = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{
	cameraPos = glm::vec3(cos(pow((float)glfwGetTime(), 2)) * 5.0, 0.5, sin(pow((float)glfwGetTime(), 2)) * 5.0);
	cameraLookDir = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUpDir = glm::vec3(0.0f, 0.5f, 0.0f);

	//view matrix
	viewMat = glm::lookAt(cameraPos, cameraTargetPos, cameraUpDir);

	//Projection matrix for pvm
	projectionMat = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);
	
	//Ortho with top left as the anchor point
	orthoMat = glm::ortho(0.0f, 800.f, 800.f, 0.0f, 0.1f, 100.0f);
}
