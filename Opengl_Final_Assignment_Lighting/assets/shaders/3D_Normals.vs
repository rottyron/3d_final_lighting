#version 460 core

//vertex stoof
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoords;
layout (location= 2) in vec3 Normal;

//inputs
uniform mat4 PVM;
uniform mat4 Model;

//outputs to fragment shader
out vec2 FragTexCoords;
out vec3 FragNormal;
out vec3 FragPos;

void main()
{
	gl_Position = PVM * vec4(Position, 1.0f);
	//pass through vertex info
	FragTexCoords = TexCoords;
	FragNormal = mat3(transpose(inverse(Model))) * Normal;
	FragPos = vec3(Model * vec4(Position, 1.0f));
}