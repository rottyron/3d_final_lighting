#pragma once
#include "includeStorage.h"
class CTimeManager
{
private:
	float fcurrentTime;
	float fpreviousTime;
	float fdeltaTime;
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


};
