//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : ShaderLoader.cpp
// Description : Callan provided the base for the shaderloader, and I was required to fill in the blanks
// I was also told this was ok to use, hence Callan's addition
// Author : James Koster-Smtih/Callan
// Mail : james.kostersmith@mediadesignschool.com
//
#include "ShaderLoader.h" 
#include<iostream>
#include<fstream>
#include<vector>

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

//Create program
GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	std::cout << "entering CreatePorgram\n";
	// Create the shaders from the filepath
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);

	// Create the program handle, attach the shaders and link it
	GLuint program = glCreateProgram();
	// ...
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);


	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		std::string programName = vertexShaderFilename + *fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	std::cout << "exiting create program\n";
	return program;
}
//Create shader
GLuint ShaderLoader::CreateShader(GLenum shaderType, const char* shaderName)
{
	std::cout << "entering create shader\n";
	// Read the shader files and save the source code as strings
	std::string strShader = ReadShaderFile(shaderName);

	// Create the shader ID and create pointers for source code string and length
	GLuint shaderID = glCreateShader(shaderType);
	std::cout << "created shaderid" << std::endl;
	const char* shader_ptr = strShader.c_str();
	const int shader_count = strShader.size();
	// ...

	glShaderSource(shaderID, 1, &shader_ptr, &shader_count);


	// Populate the Shader Object (ID) and compile
	glCompileShader(shaderID);



	// Check for errors
	int compile_result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		PrintErrorDetails(true, shaderID, shaderName);
		return 0;
	}
	std::cout << "ending shader creation\n";
	return shaderID;
}
//read shader files
std::string ShaderLoader::ReadShaderFile(const char* filename)
{
	std::cout << "entering read file\n";
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	std::cout << "read file correctly\n";
	return shaderCode;
}
//Prints any errors that might occur
void ShaderLoader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((isShader == true) ? "shader" : "program") << ": " << name << std::endl;
	std::cout << &log[0] << std::endl;
}