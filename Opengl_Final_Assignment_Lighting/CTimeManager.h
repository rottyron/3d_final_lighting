//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CTimeManager.h
// Description : Handles the time, header file
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#pragma once
#include "includeStorage.h"
class CTimeManager
{
public:
	//Initialiser
	CTimeManager();

	//Destructor
	~CTimeManager();

	//Updates the time
	void Update();

	//Returns current time
	float GetCurrentTime() { return fcurrentTime; }

	//Returns previousTime
	float GetPreviousTime() { return fpreviousTime; }

	//Returns DeltaTime
	float GetDeltaTime() { return fdeltaTime; }
	
	//unused as a function as nothing runs rendertime
	//void Render();

private:
	//Generic Variables
	float fcurrentTime;
	float fpreviousTime;
	float fdeltaTime;

};
