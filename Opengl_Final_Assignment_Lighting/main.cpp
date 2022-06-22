//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : main.cpp
// Description : Main entrance file to this program
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#define STB_IMAGE_IMPLEMENTATION
#include "includeStorage.h"
#include <vector>
#include <time.h>
#include "CCamera.h"
#include "CSpherePosition.h"
#include "CSphereRender.h"
#include "CTimeManager.h"
#include "CSkybox.h"
#include "CLightManager.h"
static const int MAX_SPHERES = 15;
GLFWwindow* mainWindow;

//SphereRenderer
CSphereRender* sphereRender;

//Vector for randomised spheres
std::vector<CSpherePosition*> spheres;

//SphereMesh 1
CSpherePosition* sphereMesh_1; //Used to rep point light Red
CSpherePosition* sphereMesh_2; //Used to rep point light Blue
CSpherePosition* sphereMesh_3; //used to rep reflections

//Camera
CCamera* mainCamera;

//Time manager holds deltaTime
CTimeManager* timeManager;

//Manages lighting
CLightManager* managedLights;

//Skybox
CSkybox* skybox;

//Camera callback vars
bool bfirstRun;
float previousX = 400; //initialize the value so the camera doesn't explode
float previousY = 400;
float xDif;
float yDif;

//Inital setup for the classes and opengl
void InitialSetup()
{
	bfirstRun = true;
	//Make window pointer -> maybe make a static pointer to it in the utilities
	mainWindow = glfwCreateWindow(800.f, 800.f, "I broke my back, smokin whisky n crack", NULL, NULL);
	glfwMakeContextCurrent(mainWindow);
	//Check if glew inited properly
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew died" << std::endl;
		system("pause");
		glfwTerminate();
	}
	stbi_set_flip_vertically_on_load(true);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Re-enable for release, off for debug
	glEnable(GL_CULL_FACE); 

	//Anti-Aliasing multi sampling active
	glEnable(GL_MULTISAMPLE);

	//Sets the clear colour for the clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Set to proper variables with a utilities static class
	glViewport(0, 0, 800.f, 800.f);

	//New sphere render witht he fideltiy and radius set (leave at 1 and scale up with scalar values to keep ez)
	sphereRender = new CSphereRender(1.f, 40);

	//Randomly generate positions for the orbs
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		if (i == 0)
		{
			spheres.push_back(new CSpherePosition("assets/textures/jerma.jpg"));
		}
		spheres.push_back(new CSpherePosition("assets/textures/Kronk.jpg"));
		spheres[i]->setObjPos(rand() % 30 - 15.0f, rand() % 30 - 15.0f, rand() % 30 - 15.0f);
	}
	//Blue SphereMesh to represent point light
	sphereMesh_1 = new CSpherePosition();
	sphereMesh_1->setObjPos(-4.0f, 6.0f, 0.0f);

	//Red Sphere Mesh
	sphereMesh_2 = new CSpherePosition();
	sphereMesh_2->setObjPos(4.0f, -6.0f, 0.0f);

	//Reflection Sphere
	sphereMesh_3 = new CSpherePosition("assets/textures/Kronk.jpg");
	sphereMesh_3->setObjPos(0.0f, 0.0f, 0.0f);

	//Camera create
	mainCamera = new CCamera();

	//skybox init, takes the camera pointer for creating pvms
	skybox = new CSkybox(mainCamera);
	timeManager = new CTimeManager();
	managedLights = new CLightManager();
}

//Setup callbacks

//callback to get mouse input and apply
void CursorInput(GLFWwindow* _mainWindow, double currentPosX, double currentPosY) 
{
	xDif += currentPosX - previousX;	//get the difference between the frames and apply them
	yDif += previousY - currentPosY;
	previousX = currentPosX;			//Make the previousX the currentX from the callback
	previousY = currentPosY;
	yDif = glm::min(yDif, 89.8f);		//Clamp the mouse rotaions below 90 to avoid gimble locking, 89.9 has not enough margin for error.
	yDif = glm::max(yDif, -89.8f);		//Clame above -89.8 to avoid gimble lock

	//Calculate the roation
	glm::vec3 rotation = glm::vec3(
		cos(glm::radians(xDif)) * cos(glm::radians(yDif)),		//rotation about the x axis *between 180 -180 (left/right)
		sin(glm::radians(yDif)),								//Rotation about the y axis, between -90 and 90 degrees(up/down)
		sin(glm::radians(xDif)) * cos(glm::radians(yDif)));		//rotation about the z axis (between 180 and -180 degrees(roll)
 
	mainCamera->AddCameraRotation(glm::normalize(rotation) * timeManager->GetDeltaTime());	//Apply the new rotation to the camera, normalize and multiply by deltatime

}

//UPDATE/RENDER PIPELINE

//Updates all targets
void Update()
{
	timeManager->Update();
	glfwPollEvents();
	glfwSetCursorPosCallback(mainWindow, CursorInput);
	mainCamera->Update(mainWindow, timeManager->GetDeltaTime());
	for (int i = 0; i < MAX_SPHERES; i++)						//Update all the orbs
	{
		if (spheres[i] != nullptr)
		{
			spheres[i]->Update(timeManager->GetDeltaTime());
		}
	}
	sphereMesh_1->Update(timeManager->GetDeltaTime());
	sphereMesh_2->Update(timeManager->GetDeltaTime());
	sphereMesh_3->Update(timeManager->GetDeltaTime());
	skybox->Update(timeManager->GetDeltaTime());
	managedLights->Update(timeManager->GetDeltaTime());

}

//Renders all targets
void Render()
{
	glm::mat4 PVM;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mainCamera->PassCameraPos(sphereRender->GetSphereProg());
	//For loop to render the general orbs
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		if (spheres[i] != nullptr)				//Render the orbs appropriately 
		{
			if (i == 0)
			{
				sphereRender->RenderRim(sphereRender->GetRimProg(),
					spheres[i], mainCamera);
			}
			else
			{
				sphereRender->Render(sphereRender->GetSphereProg(),
					spheres[i], mainCamera);
			}
		}
	}
	//Orbs representing point lights *needs their pvm calced outside*
	PVM = mainCamera->CreatePVM(sphereMesh_1->GetModel());
	sphereRender->Render(sphereRender->GetSphereBlue(), sphereMesh_1->GetModel(), &PVM);

	PVM = mainCamera->CreatePVM(sphereMesh_2->GetModel());
	sphereRender->Render(sphereRender->GetSphereRed(), sphereMesh_2->GetModel(), &PVM);

	//Render Reflecting Orb
	sphereRender->RenderReflect(sphereRender->GetSphereReflect(),
		skybox->GetTextureId(), sphereMesh_3, mainCamera);

	//Render Skybox
	skybox->Render();

	glfwSwapBuffers(mainWindow);
}

//Main entry for the program
int main()
{
	//set the rng seed
	srand(time(0));
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_SAMPLES, 4);
	InitialSetup();
	//General Render Pipeline
	while (glfwWindowShouldClose(mainWindow) == false)
	{
		Update();
		Render();
	}
	
}