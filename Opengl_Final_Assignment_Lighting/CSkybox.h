#pragma once
#include "includeStorage.h"
#include "CCamera.h"
class CSkybox
{
public:
	CSkybox(CCamera* _camera);
	~CSkybox();
	void Update();
	void Render();
private:
	std::string filePaths[6];
	CCamera* cam;
	GLuint textureID;

	glm::mat4 modelMat;
	glm::mat4 PVM;
	GLuint skyboxProg;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	int indiciesSize;
	
};

