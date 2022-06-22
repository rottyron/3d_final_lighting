//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CCamera.h
// Description : camera header
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#pragma once
#include "includeStorage.h"
//Holds the camera Data
class CCamera
{
public:
	//Initializer
	CCamera();
	//Destructor
	~CCamera();
	//Generic Update Function (per frame)
	void Update(GLFWwindow* _mainWindow, float _deltaTime);
	//Callback to process inputs for the camera
	void ProcessInput(GLFWwindow* _mainWindow, float _deltaTime);
	//Getters
	glm::mat4* GetProjectionMat() { return &projectionMat; }
	glm::mat4* GetViewMat() { return &viewMat; }
	glm::mat4 CreatePVM(glm::mat4* _model) { return projectionMat * viewMat * *_model; }
	glm::mat4 GetPVMat() { return projectionMat * viewMat; }
	//Used for adding rotation to the camera
	void AddCameraRotation(glm::vec3 _lookDir) { cameraLookDir = _lookDir; }
	//Pass the cameraPosition to the shader of the program
	void PassCameraPos(GLuint* prog);
private:
	//View and projection for the PVM
	glm::mat4 viewMat;
	glm::mat4 projectionMat;
	glm::mat4 orthoMat;

	glm::vec3 cameraPos;
	glm::vec3 cameraLookDir;
	glm::vec3 cameraTargetPos;
	glm::vec3 cameraUpDir;

	//camspeed 
	const float camSpeed = 10.0f;

};

