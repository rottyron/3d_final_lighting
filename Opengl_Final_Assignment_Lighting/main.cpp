#define STB_IMAGE_IMPLEMENTATION
#include "includeStorage.h"
#include <vector>
#include <time.h>
#include "CCamera.h"
#include "CSphereMesh.h"
#include "CSphereRender.h"
#include "CTimeManager.h"
#include "CSkybox.h"
#include "CLightManager.h"
static const int MAX_SPHERES = 15;
GLFWwindow* mainWindow;

//SphereRenderer
CSphereRender* sphereRender;
std::vector<CSphereMesh*> spheres;
//SphereMesh 1
CSphereMesh* sphereMesh_1;
CSphereMesh* sphereMesh_2;
CCamera* mainCamera;

CTimeManager* timeManager;

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
	glEnable(GL_DEPTH_TEST);
	//Re-enable for release, off for debug
	glEnable(GL_CULL_FACE); 
	//Anti-Aliasing multi sampling active
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Set to proper variables with a utilities static class
	glViewport(0, 0, 800.f, 800.f);
	sphereRender = new CSphereRender(1.f, 40);
	//Randomly generate positions for the orbs
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		if (i == 0)
		{
			spheres.push_back(new CSphereMesh("assets/textures/jerma.jpg"));
		}
		spheres.push_back(new CSphereMesh("assets/textures/Kronk.jpg"));
		spheres[i]->setObjPos(rand() % 15, rand() % 15, rand() % 15);
	}
	mainCamera = new CCamera();
	//skybox init, takes the camera pointer for creating pvms
	skybox = new CSkybox(mainCamera);
	timeManager = new CTimeManager();
	managedLights = new CLightManager();
}

//Setup callbacks
void CursorInput(GLFWwindow* _mainWindow, double currentPosX, double currentPosY) //callback to get mouse input and apply
{
	xDif += currentPosX - previousX;	//get the difference between the frames and apply them
	yDif += previousY - currentPosY;
	previousX = currentPosX;			//Make the previousX the currentX from the callback
	previousY = currentPosY;
	yDif = glm::min(yDif, 89.8f);		//Clamp the mouse rotaions below 90 to avoid gimble locking, 89.9 has not enough margin for error.
	yDif = glm::max(yDif, -89.8f);


										//Raw math calculations for roll pitch and yaw
										//convert to radians
										//yaw: cos(difference in x)*cos(difference in y)	rotation around the x
										//pitch: (sin(difference in y)		rotation around the y
										//roll: sin(difference in x)*cos(difference in y)	rotation around the z

	glm::vec3 rotation = glm::vec3(
		cos(glm::radians(xDif)) * cos(glm::radians(yDif)),		//rotation about the x axis *between 180 -180 (left/right)
		sin(glm::radians(yDif)),								//Rotation about the y axis, between -90 and 90 degrees(up/down)
		sin(glm::radians(xDif)) * cos(glm::radians(yDif)));		//rotation about the z axis (between 180 and -180 degrees(roll)
 
	mainCamera->AddCameraRotation(glm::normalize(rotation) * timeManager->GetDeltaTime());	//Apply the new vector to the camera, normalize and multiply by deltatime

}

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
	skybox->Update(timeManager->GetDeltaTime());
	managedLights->Update(timeManager->GetDeltaTime());

}

//Renders all targets
void Render()
{
	glm::mat4 PVM;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		if (spheres[i] != nullptr)				//Render the orbs appropriately 
		{
			if (i == 0)
			{
				PVM = mainCamera->CreatePVM(spheres[i]->GetModel());
				sphereRender->Render(sphereRender->GetRimProg(), spheres[i]->GetTexture(), spheres[i]->GetModel(), &PVM);
			}
			else
			{
				PVM = mainCamera->CreatePVM(spheres[i]->GetModel());
				sphereRender->Render(sphereRender->GetSphereProg(), spheres[i]->GetTexture(), spheres[i]->GetModel(), &PVM);
			}
		}
	}
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