#include "CTimeManager.h"
CTimeManager::CTimeManager()
{
	fcurrentTime = 0.f;
	fpreviousTime = (float)glfwGetTime();
	fdeltaTime = 0.f;
}
//Destructor
CTimeManager::~CTimeManager()
{
}
//Update the time
void CTimeManager::Update()
{
	fcurrentTime = (float)glfwGetTime();
	fdeltaTime = fcurrentTime - fpreviousTime;
	fpreviousTime = fcurrentTime;
}
