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

//Skybox
CSkybox* skybox;
//Inital setup for the classes and opengl
void InitialSetup()
{
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
}

//Updates all targets
void Update()
{
	glfwPollEvents();
	mainCamera->Update();
	sphereMesh_1->Update();
	skybox->Update();

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