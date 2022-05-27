//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : ShaderLoader.h
// Description : Header for the shader loader
// Author : James Koster-Smtih/Callan
// Mail : james.kostersmith@mediadesignschool.com
//
#pragma once

// Library Includes
#include "IncludeStorage.h"

class ShaderLoader
{
	
public:	
	//Static function for creating the program
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);

private:
	//Initialiser
	ShaderLoader(void);
	//destructror
	~ShaderLoader(void);
	//Creates the shader
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	//Reads the shader File
	static std::string ReadShaderFile(const char *filename);
	//Prints any errors that might occur
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
