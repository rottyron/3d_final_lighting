//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Skybox.vs
// Description : Skybox vertex shader, handles cubeMap calcs
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#version 460 core

//vertex data interp
layout (location = 0) in vec3 Position;

//inputs
uniform mat4 PVM;

//Outputs to frag shader
out vec3 FragTexCoords;

void main()
{
	gl_Position = PVM * vec4(Position, 1.0f);
	FragTexCoords = Position;
}