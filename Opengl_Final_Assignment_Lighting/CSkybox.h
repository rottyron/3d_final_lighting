//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CSkybox.h
// Description : Skybox header file
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#pragma once
#include "includeStorage.h"
#include "CCamera.h"
class CSkybox
{
public:
	//initializer *must take camera*
	CSkybox(CCamera* _camera);

	//Destructor
	~CSkybox();

	//Generic Update per frame etc etc
	void Update(float _deltaTime);

	//Render function
	void Render();

	//Getters
	GLuint* GetTextureId() { return &textureID; }

private:
	//File paths hold the strings for the cubemap files
	std::string filePaths[6];

	//Camera pointer
	CCamera* cam;

	//Texture Id
	GLuint textureID;

	//Generic Variables
	glm::mat4 modelMat;
	glm::mat4 PVM;
	GLuint skyboxProg;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	int indiciesSize;
	
};

