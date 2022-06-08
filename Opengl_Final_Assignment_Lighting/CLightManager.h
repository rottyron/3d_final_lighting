#pragma once
#include "includeStorage.h"
class CLightManager
{
public:
	CLightManager();
	~CLightManager();
	void Update(float _deltaTime);
	void PassPointLights(GLuint* _program);
private:
	struct pointLight
	{
		glm::vec3 position;
		glm::vec3 color;
		float ambientStrength;
		float specularStrength;
	};
	static const int MAX_POINT_LIGHTS = 4;
	pointLight pointLights[MAX_POINT_LIGHTS];

};

