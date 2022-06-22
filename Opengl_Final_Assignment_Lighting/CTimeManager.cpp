//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CTimeManager.cpp
// Description : Handles time
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#include "CTimeManager.h"
//initialiser
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
//Updates the time
void CTimeManager::Update()
{
	fcurrentTime = (float)glfwGetTime();
	fdeltaTime = fcurrentTime - fpreviousTime;
	fpreviousTime = fcurrentTime;
}
