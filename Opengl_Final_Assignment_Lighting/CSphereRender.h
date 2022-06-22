//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CSphereRender.h
// Description : Header for the sphere Render
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#pragma once
#include "includeStorage.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "CCamera.h"
#include "CSpherePosition.h"
//Holds the VAO VBO and EBO and renders the target
class CSphereRender
{
public:
	//Initializer
	CSphereRender(float _radius, int _fidelity);
	//Desturctor
	~CSphereRender();
	//Render an orb, no texture only color
	void Render(GLuint* _prog, glm::mat4* _modelMat, glm::mat4* _PVM);
	//Render using an overloaded program, and texture and camera
	void Render(GLuint* _prog, CSpherePosition* _sphere, CCamera* _mainCam);\
	//Render RimLightOrbs
	void RenderRim(GLuint* _prog, CSpherePosition* _sphere, CCamera* _mainCam);
	//Render using an overloaded program, and texture, camera and cubemap
	void RenderReflect(GLuint* _prog, GLuint* _skyTexture, CSpherePosition* _sphere, CCamera* _mainCamera);
	//Getters
	GLuint* GetVAO() { return &VAO; } //for collecting the vao
	GLuint* GetSphereProg() {return &sphereProg;}
	GLuint* GetRimProg() {return &sphereRimProg;}
	GLuint* GetSphereRed() {return &sphereRed;}
	GLuint* GetSphereBlue() {return &sphereBlue;}
	GLuint* GetSphereReflect() {return &sphereReflect;}

private:
	//Generic variables
	GLuint VAO;
	int indexCount;
	int drawType;

	//defaults
	//Creates the default program to use for this, the render can be overloaded
	GLuint sphereRimProg = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dLight_BlinnPhongRim.fs");
	GLuint sphereProg = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dLight_BlinnPhong.fs");
	GLuint sphereRed = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dColorRed.fs");
	GLuint sphereBlue = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dColorBlue.fs");
	GLuint sphereReflect = ShaderLoader::CreateProgram("assets/shaders/3D_Normals.vs", "assets/shaders/3dReflect.fs");
	//Default texture
	GLuint texture;
	int imageWidth;
	int imageHeight;
	int imageComponents;

};

