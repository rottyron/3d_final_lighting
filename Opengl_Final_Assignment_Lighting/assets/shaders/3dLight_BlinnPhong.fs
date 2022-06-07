#version 460 core

//Vertex Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

//uniform inputs
uniform sampler2D ImageTexture0;
uniform vec3 CameraPos;
uniform float AmbientStrength			= 0.2f;
uniform vec3 AmbientColor				= vec3(1.0f,1.0f,1.0f);
uniform vec3 LightColor					= vec3(1.0f,1.0f,1.0f);
uniform vec3 LightPos					= vec3(-2.0f, 6.0f, 3.0f);
uniform float LightSpecularStrength		= 1.0f;
uniform float Shininess					= 16.0f;

//output
out vec4 FinalColor;

void main()
{
	// Light direction
	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - LightPos);

	//ambient Component
	vec3 Ambient = AmbientStrength * AmbientColor;

	//Diffuse Componenet
	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * LightColor;
	
	//Specula stuff
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);
	
	//Phong model
	//vec3 ReflectedDir = reflect(LightDir, Normal);
	//float SpecularReflectivity = pow(max(dot(ReverseViewDir, ReflectedDir), 0.0f), Shininess);

	//Blin phong model
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
	
	vec3 Specular = LightSpecularStrength * SpecularReflectivity * LightColor;

	//combine the lighting components
	vec4 Light = vec4(Ambient + Diffuse + Specular, 1.0f);

	
	//calculate the final color
	FinalColor = Light * texture(ImageTexture0, FragTexCoords);
}