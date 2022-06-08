#version 460 core
#define MAX_POINT_LIGHTS 4
struct pointLight
{
	vec3 position;
	vec3 color;
	float ambientStrength;
	float specularStrength;
};

//Vertex Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

//uniform inputs
uniform sampler2D ImageTexture0;
uniform pointLight pointLights[MAX_POINT_LIGHTS];
uniform vec3 CameraPos;
uniform vec3 AmbientColor				= vec3(1.0f,1.0f,1.0f);
uniform float Shininess					= 16.0f;

//output
out vec4 FinalColor;

//Looped function to calculate the individual lights
vec3 CalculateLight_Point(pointLight _light)
{
	// Light direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - _light.position);

	//ambient Component
	vec3 Ambient = _light.ambientStrength * AmbientColor;

	//Diffuse Componenet
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * _light.color;
	
	//Specula stuff
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);

	//Blin phong model
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
	
	vec3 Specular = _light.specularStrength * SpecularReflectivity * _light.color;

	//combine the lighting components
	vec3 Light = Ambient + Diffuse + Specular;
	return Light;
}

//Main
void main()
{
	vec3 LightOutput = vec3(0.0f,0.0f,0.0f);
	for(int i = 0; i < MAX_POINT_LIGHTS; i++)				//For loop, loops through all the lights and adds them together
	{
		LightOutput += CalculateLight_Point(pointLights[i]);
	}
	FinalColor = vec4(LightOutput, 1.0f) * texture(ImageTexture0, FragTexCoords);
}