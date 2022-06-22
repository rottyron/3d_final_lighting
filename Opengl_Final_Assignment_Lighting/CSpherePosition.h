//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name :CSpherePosition.h 
// Description : Holds the variables for the sphere, and if moved would update them aswell
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#pragma once
#include "includeStorage.h"
//Holds position data, texture data and sends to the renderer
class CSpherePosition
{
public:
	//initializer
	CSpherePosition();

	//Initialise with a custom texture
	CSpherePosition(std::string _texture);

	//Destructor
	~CSpherePosition();

	//Generic Update Function
	void Update(float _deltaTime);

	//Getters/Setters
	glm::mat4* GetModel() { return &modelMat; }
	GLuint* GetTexture() { return &texture; }
	void setObjPos(float _x, float _y, float _z) { objPosition = glm::vec3(_x, _y, _z); }

private:
	//Generic Variables
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

