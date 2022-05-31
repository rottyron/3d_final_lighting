#version 460 core

//Vertex inputs
in vec3 FragTexCoords;

//Uniforms
uniform samplerCube Texture0;

//output
out vec4 FinalColor;

void main()
{
	FinalColor = texture(Texture0, FragTexCoords);
}