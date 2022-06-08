#pragma once
#include "includeStorage.h"
class CLightManager
{
public:
private:
	struct pointLight
	{
		glm::vec3 Position;
		glm::vec3 Color;
		float AmbientStrength;
		float SpecularStrength;
	};
	static const int MAX_POINT_LIGHTS = 4;
	pointLight pointLights[MAX_POINT_LIGHTS];

};

