//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : skybox.fs
// Description : This is the skybox fragment Shader, it deals with the cubemap
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

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