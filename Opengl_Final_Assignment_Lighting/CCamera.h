#pragma once
#include "includeStorage.h"
//Holds the camera Data
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Update();
	glm::mat4* GetProjectionMat() { return &projectionMat; }
	glm::mat4* GetViewMat() { return &viewMat; }
	glm::mat4 CreatePVM(glm::mat4* _model) { return projectionMat * viewMat * *_model; }
	
private:
	//View and projection for the PVM
	glm::mat4 viewMat;
	glm::mat4 projectionMat;
	glm::mat4 orthoMat;

	glm::vec3 cameraPos;
	glm::vec3 cameraLookDir;
	glm::vec3 cameraTargetPos;
	glm::vec3 cameraUpDir;

};

