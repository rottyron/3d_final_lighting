#define STB_IMAGE_IMPLEMENTATION
#include "includeStorage.h"
#include "CCamera.h"
#include "CSphereMesh.h"
#include "CSphereRender.h"
#include "CTimeManager.h"
#include "CSkybox.h"

GLFWwindow* mainWindow;

//SphereRenderer
CSphereRender* sphereRender;
//SphereMesh 1
CSphereMesh* sphereMesh_1;
CCamera* mainCamera;

CTimeManager* timeManager;

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
	//glEnable(GL_CULL_FACE); 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Set to proper variables with a utilities static class
	glViewport(0, 0, 800.f, 800.f);
	sphereRender = new CSphereRender(1.f, 40);
	sphereMesh_1 = new CSphereMesh("assets/textures/earf.jpg");
	mainCamera = new CCamera();
	//skybox init, takes the camera pointer for creating pvms
	skybox = new CSkybox(mainCamera);
	timeManager = new CTimeManager();
}

//Setup callbacks
void CursorInput(GLFWwindow* _mainWindow, double currentPosX, double currentPosY) //callback to get mouse input and apply
{

	//needs: mouse input, apply that to camera to move it's look pos using pitch and yaw, not roll
	//only want to restrict the vertical look dir, not horizontal
	//Problems: can't use the class variables, use a bool *fixed, put in the main
	/*How
	calculate the mouse offset since last frame
	add the x and y to yaw and pitch rotations
	lock the min/max look dirs - tried to use glm::min/max and it exploded - resulting in if statements
	calculate the vector - done, had to refresh over the math rules ;-;
	*/

	xDif += currentPosX - previousX;	//get the difference between the frames and apply them
	yDif += previousY - currentPosY;
	previousX = currentPosX;
	previousY = currentPosY;

	if (yDif > 89.8f)
	{
		yDif = 89.8f;
	}
	if (yDif < -89.8f)
	{
		yDif = -89.8f;
	}
	//Raw math calculations for roll pitch and yaw
	// calculate to radians **haha glm let's me just call a function ;-;)
	//yaw: cos(difference in x)*cos(difference in y)	rotation around the x
	//pitch: (sin(difference in y)		rotation around the y
	//roll: sin(difference in x)*cos(difference in y)	rotation around the z
	glm::vec3 rotation; //calculating the rotation vector
	rotation.x = cos(glm::radians(xDif)) * cos(glm::radians(yDif));	//rotation about the x axis *between 180 -180 (left/right)
	rotation.y = sin(glm::radians(yDif));								//Rotation about the y axis, between -90 and 90 degrees(up/down)
	rotation.z = sin(glm::radians(xDif)) * cos(glm::radians(yDif));	//rotation about the z axis (between 180 and -180 degrees(roll)
	mainCamera->AddCameraRotation(glm::normalize(rotation) * timeManager->GetDeltaTime());

}

//Updates all targets
void Update()
{
	timeManager->Update();
	glfwPollEvents();
	glfwSetCursorPosCallback(mainWindow, CursorInput);
	mainCamera->Update(mainWindow, timeManager->GetDeltaTime());
	sphereMesh_1->Update(timeManager->GetDeltaTime());
	skybox->Update(timeManager->GetDeltaTime());

}

//Renders all targets
void Render()
{
	glm::mat4 PVM;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	PVM = mainCamera->CreatePVM(sphereMesh_1->GetModel());
	sphereRender->Render(sphereMesh_1->GetTexture(), sphereMesh_1->GetModel(), &PVM);
	skybox->Render();
	glfwSwapBuffers(mainWindow);
}

//Main entry for the program
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	InitialSetup();
	//General Render Pipeline
	while (glfwWindowShouldClose(mainWindow) == false)
	{
		Update();
		Render();
	}
	
}