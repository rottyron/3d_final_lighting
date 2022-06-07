#pragma once
#include "includeStorage.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
//Holds the VAO VBO and EBO and renders the target
class CSphereRender
{
public:
	CSphereRender(float _radius, int _fidelity);
	~CSphereRender();
	//Render using the default program, and debug texture
	void Render(glm::mat4* _modelMat, glm::mat4* _PVM);
	//Render using the default program, but overloaded texture
	void Render(GLuint* _texture, glm::mat4* _modelMat, glm::mat4* _PVM);
	//Render using an overloaded program, and texture
	void Render(GLuint* _prog, GLuint* _texture, glm::mat4* _modelMat, glm::mat4* _PVM);
	GLuint* GetVAO() { return &VAO; } //for collecting the vao

	GLuint* GetSphereProg() { return &sphereProg; }
	GLuint* GetRimProg() { return &sphereRimProg; }
private:
	GLuint VAO;
	int indexCount;
	int drawType;

	//defaults
	//Creates the default program to use for this, the render can be overloaded
	GLuint sphereProg = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dLight_BlinnPhongRim.fs");
	GLuint sphereRimProg = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dLight_BlinnPhong.fs");
	//Default texture
	GLuint texture;
	int imageWidth;
	int imageHeight;
	int imageComponents;
};

