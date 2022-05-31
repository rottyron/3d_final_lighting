#include "CSkybox.h"

CSkybox::CSkybox(CCamera* _camera)
{
	skyboxProg = ShaderLoader::CreateProgram("assets/shaders/Skybox.vs", "assets/shaders/Skybox.fs");
	cam = _camera;
	GLfloat vertices[] = {
		//index		Position					
		//index		Position			
		//Front Quad
		/*0*/	   -0.5f,	0.5f,		0.5f,	
		/*1*/	   -0.5f,	-0.5f,	0.5f,	
		/*2*/		0.5f,	-0.5f,	0.5f,	
		/*3*/		0.5f,	0.5f,	0.5f,		

		//Back Quad
		/*0*/		 0.5f,  0.5f, -0.5f,
		/*1*/		 0.5f, -0.5f, -0.5f,
		/*2*/		-0.5f, -0.5f, -0.5f,
		/*3*/		-0.5f,  0.5f, -0.5f,

		//Right Quad
		/*0*/		0.5f,  0.5f,  0.5f,	
		/*1*/		0.5f, -0.5f,  0.5f,	
		/*2*/		0.5f, -0.5f, -0.5f,	
		/*3*/		0.5f,  0.5f, -0.5f,	

		//Left Quad
		/*0*/		-0.5f, 0.5f,-0.5f,	
		/*1*/		-0.5f,-0.5f,-0.5f,	
		/*2*/		-0.5f,-0.5f, 0.5f,	
		/*3*/		-0.5f, 0.5f, 0.5f,	

		//Top Quad
		/*0*/		-0.5f, 0.5f,-0.5f,	
		/*1*/		-0.5f, 0.5f, 0.5f,	
		/*2*/		 0.5f, 0.5f, 0.5f,	
		/*3*/		 0.5f, 0.5f,-0.5f,	

		//Bottom Quad
		/*0*/	   -0.5f,-0.5f, 0.5f,	
		/*1*/	   -0.5f,-0.5f,-0.5f,	
		/*2*/	    0.5f,-0.5f,-0.5f,	
		/*3*/	    0.5f,-0.5f, 0.5f,	

	};

	GLuint Indicies[] = {
		0,	2,	1,	//Front Tri 1
		0,	3,	2,	//Front Tri 2
		4,	6,	5,	//Back Tri 1
		4,	7,	6,	//Back Tri 2
		8,	10,	9,	//Right Tri 1
		8,	11,	10,	//Right Tri 2
		12,	14,	13,	//Left Tri 1
		12,	15,	14,	//Left Tri 2
		16,	18,	17,	//Top Tri 1
		16,	19,	18,	//Top Tri 2
		20,	22,	21,	//Bottom Tri 1
		20,	23,	22,	//Bottom Tri 2
		//36
	};
	//Get the size of the indices for later
	indiciesSize = sizeof(Indicies) / 4;

	filePaths[0] = "Right.jpg";
	filePaths[1] = "Left.jpg";
	filePaths[2] = "Up.jpg";
	filePaths[3] = "Down.jpg";
	filePaths[4] = "Back.jpg";
	filePaths[5] = "Front.jpg";
	GL_TEXTURE_CUBE_MAP_POSITIVE_X;	//right
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X;	//LEFT
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y; //TOP
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; //BOT
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z;	//BACK
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; //FRONT
	
	//Bind texture template
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// Load image data
	int imageWidth;
	int imageHeight;
	int imageComponents;
	stbi_set_flip_vertically_on_load(false);

	for (int i = 0; i < 6; i++)
	{
		std::string FullFilePath = "assets/textures/Cubemaps/MountainOutpost/" + filePaths[i];
		std::cout << FullFilePath << std::endl;
		unsigned char* imageData = stbi_load(FullFilePath.c_str(), &imageWidth, &imageHeight, &imageComponents, 0);

		//Check if it's rgb or rgba
		GLint LoadedComponents = (imageComponents == 4) ? GL_RGBA : GL_RGB;

		//Populate texture with image data
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, LoadedComponents, imageWidth, imageHeight, 0,
			LoadedComponents, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

	//set the texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Generate Mipmaps
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	//Unbind texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//Generate VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indicies), Indicies, GL_STATIC_DRAW);

	//VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Set attributes **ONLY POSITION ON THIS ONE**

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

}

CSkybox::~CSkybox()
{
}

void CSkybox::Update()
{
	modelMat = glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));
	PVM = cam->CreatePVM(&modelMat);
}

void CSkybox::Render()
{
	glUseProgram(skyboxProg);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(glGetUniformLocation(skyboxProg, "Texture0"), 0);
	glUniformMatrix4fv(glGetUniformLocation(skyboxProg, "PVM"), 1, GL_FALSE, glm::value_ptr(PVM));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
}
