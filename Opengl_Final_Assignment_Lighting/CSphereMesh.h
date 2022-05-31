#pragma once
#include "includeStorage.h"
//Holds position data, texture data and sends to the renderer
class CSphereMesh
{
public:
	CSphereMesh(std::string _texture);
	~CSphereMesh();
	void Update();
	glm::mat4* GetModel() { return &modelMat; }
	GLuint* GetTexture() { return &texture; }

private:
	glm::vec3 objPosition;
	float objAngle;
	glm::vec3 objScale;
	glm::mat4 scaleMat;
	glm::mat4 translationMat;
	glm::mat4 rotationMat;
	glm::mat4 modelMat;

	glm::mat4 PVM;
	GLuint texture;
	int imageWidth = 0;
	int imageHeight = 0;
	int	imageComponents = 0;
};
