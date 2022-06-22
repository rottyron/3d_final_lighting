//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CSpherePosition.cpp
// Description : Handles all of the individual sphere data that I wanted to be adjustable easily
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//

#include "CSpherePosition.h"

//initialiser
CSpherePosition::CSpherePosition()
{
	objPosition = glm::vec3(0.0f, 0.f, 0.f);
	objAngle = 0.0f;
	objScale = glm::vec3(1.f);
}

//Initialise with a custom texture
CSpherePosition::CSpherePosition(std::string _texture)
{
	objPosition = glm::vec3(0.0f,0.f,0.f);
	objAngle = 0.0f;
	objScale = glm::vec3(1.f);

	//IMAGE SETUP
//get the data for the image
	unsigned char* ImageData = stbi_load(_texture.c_str(),
		&imageWidth, &imageHeight, &imageComponents, 0);

	//Texture Binding
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//setting the filtering and mipmap parameters for this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Check How many components the loaded image has rgb or rgba
	GLint LoadedComponents = (imageComponents == 4) ? GL_RGBA : GL_RGB;

	//Populate said texture with image data
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, imageWidth, imageHeight, 0,
		LoadedComponents, GL_UNSIGNED_BYTE, ImageData);

	//Generate Mipmaps, free the memory and unbind texture
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(ImageData); //we love unbinding for memory going brr
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Destructor
CSpherePosition::~CSpherePosition()
{
}

//Generic update per frame
void CSpherePosition::Update(float _deltaTime)
{
	translationMat = glm::translate(glm::mat4(), objPosition);
	rotationMat = glm::rotate(glm::mat4(), glm::radians(objAngle), glm::vec3(0.1f, 0.0f, 0.0f));
	scaleMat = glm::scale(glm::mat4(), objScale);
	modelMat = translationMat * rotationMat * scaleMat;
}
