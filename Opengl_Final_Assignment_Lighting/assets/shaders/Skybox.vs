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