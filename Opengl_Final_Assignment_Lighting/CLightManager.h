#pragma once
#include "includeStorage.h"
class CLightManager
{
public:
	CLightManager();
	~CLightManager();
	void Update(float _deltaTime);
	void PassLights(GLuint* _program);
private:
	struct pointLight
	{
		glm::vec3 position;
		glm::vec3 color;
		float ambientStrength;
		float specularStrength;

		float attenuationConstant;
		float attenuationLinear;
		float attenuationExponent;
	};
	struct directionalLight
	{
		glm::vec3 direction;
		glm::vec3 color;
		float ambientStrength;
		float specularStrength;
	};
	static const int MAX_POINT_LIGHTS = 4;
	pointLight pointLights[MAX_POINT_LIGHTS];
	directionalLight directLight;

};

