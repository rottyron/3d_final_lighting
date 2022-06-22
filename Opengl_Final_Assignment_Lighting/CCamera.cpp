//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CCamera.cpp
// Description : camera project file, handles everything to dow ith the camera
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#include "CCamera.h"

//initilaizer 
CCamera::CCamera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);		//actual camera position
	cameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);	//target
	//cameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);		//updir
}

//destructor
CCamera::~CCamera()
{
}

//updates per frame
void CCamera::Update(GLFWwindow* _mainWindow, float _deltaTime)
{
	glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //disable cursor set mouse as input
	ProcessInput(_mainWindow, _deltaTime);

	//view matrix
	viewMat = glm::lookAt(cameraPos, cameraPos + cameraLookDir, cameraUpDir);

	//Projection matrix for pvm
	projectionMat = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 4000.0f);
	
	//Ortho with top left as the anchor point
	orthoMat = glm::ortho(0.0f, 800.f, 800.f, 0.0f, 0.1f, 4000.0f);
}

//Process input then move the camera for a proper spectate cam
void CCamera::ProcessInput(GLFWwindow* _mainWindow, float _deltaTime) 
{

	if (glfwGetKey(_mainWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos +=  glm::normalize(cameraLookDir) * camSpeed * _deltaTime; //using look dir as forward vector
	}
	if (glfwGetKey(_mainWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(cameraLookDir) * camSpeed * _deltaTime; //using look dir as forward vector
	}	
	if (glfwGetKey(_mainWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		//need a vector for strafe, so a vector prependicular between the up and the look dir should suffice, 
		//use a dot product to get that
		cameraPos -= glm::normalize(glm::cross(cameraLookDir, cameraUpDir)) * camSpeed * _deltaTime; 
	}	
	if (glfwGetKey(_mainWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		//need a vector for strafe, so a vector prependicular between the up and the look dir should suffice,
		//use a dot product to get that
		cameraPos += glm::normalize(glm::cross(cameraLookDir, cameraUpDir)) * camSpeed * _deltaTime;
	}
	if (glfwGetKey(_mainWindow, GLFW_KEY_SPACE) == GLFW_PRESS) //Makes the camera go up
	{
		cameraPos += glm::normalize(cameraUpDir) * camSpeed * _deltaTime;
	}
	if (glfwGetKey(_mainWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) //Makes the caemra go down
	{
		cameraPos -= glm::normalize(cameraUpDir) * camSpeed * _deltaTime;
	}
}

//Psses the camera position into the shader
void CCamera::PassCameraPos(GLuint* _prog)
{
	glUniform3fv(glGetUniformLocation(*_prog, "CameraPos"), 1, glm::value_ptr(cameraPos));
}
