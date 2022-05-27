#version 460 core

//Vertex Inputs
in vec2 FragTexCoords;
in vec3 FragNormal;

//uniform inputs
uniform sampler2D ImageTexture0;
uniform float AmbientStrength = 1.0f;
uniform vec3 AmbientColor = vec3(1.0f,1.0f,1.0f);

//output
out vec4 FinalColor;

void main()
{
	//ambient Component
	vec3 Ambient = AmbientStrength * AmbientColor;
	
	//combine the lighting components
	vec4 Light = vec4(Ambient, 1.0f);
	
	//calculate the final color
	FinalColor = Light * texture(ImageTexture0, FragTexCoords);
}