#include "CSphereRender.h"
#include "CLightManager.h"

CLightManager* lights = new CLightManager();

CSphereRender::CSphereRender(float _radius, int _fidelity)
{
	int VertexAttrib = 8;	// Float components are needed for each vertex point
	int IndexPerQuad = 6;	// Indices needed to create a quad

	// Angles to keep track of the sphere points 
	float Phi = 0.0f;
	float Theta = 0.0f;

	// Create the vertex array to hold the correct number of elements based on the fidelity of the sphere
	int VertexCount = _fidelity * _fidelity * VertexAttrib;
	GLfloat* Vertices = new GLfloat[VertexCount];
	int Element = 0;

	// Each cycle moves down on the vertical (Y axis) to start the next ring
	for (int i = 0; i < _fidelity; i++)
	{
		// A new  horizontal ring starts at 0 degrees
		Theta = 0.0f;

		// Creates a horizontal ring and adds each new vertex point to the vertex array
		for (int j = 0; j < _fidelity; j++)
		{
			// Calculate the new vertex position point with the new angles
			float x = cos(Phi) * sin(Theta);
			float y = cos(Theta);
			float z = sin(Phi) * sin(Theta);

			// Set the position of the current vertex point
			Vertices[Element++] = x * _radius;
			Vertices[Element++] = y * _radius;
			Vertices[Element++] = z * _radius;

			// Set the texture coordinates of the current vertex point
			Vertices[Element++] = (float)i / (_fidelity - 1);
			Vertices[Element++] = 1 - ((float)j / (_fidelity - 1)); // 1 minus in order to flip the direction of 0-1 (0 at the bottom)

			// Set the normal direction of the current vertex point
			Vertices[Element++] = x;
			Vertices[Element++] = y;
			Vertices[Element++] = z;

			// Theta (Y axis) angle is incremented based on the angle created by number of sections
			// As the sphere is built ring by ring, the theta is only needed to do half the circumferance therefore using just PI
			Theta += ((float)M_PI / ((float)_fidelity - 1.0f));
		}

		// Phi angle (X and Z axes) is incremented based on the angle created by the number of sections
		// Angle uses 2*PI to get the full circumference as this layer is built as a full ring
		Phi += (2.0f * (float)M_PI) / ((float)_fidelity - 1.0f);
	}

	// Create the index array to hold the correct number of elements based on the fidelity of the sphere
	indexCount = _fidelity * _fidelity * IndexPerQuad;
	GLuint* Indices = new GLuint[indexCount];

	Element = 0;	// Reset the element offset for the new array
	for (int i = 0; i < _fidelity; i++)
	{
		for (int j = 0; j < _fidelity; j++)
		{
			// First triangle of the quad
			Indices[Element++] = (((i + 1) % _fidelity) * _fidelity) + ((j + 1) % _fidelity);
			Indices[Element++] = (i * _fidelity) + (j);
			Indices[Element++] = (((i + 1) % _fidelity) * _fidelity) + (j);

			// Second triangle of the quad
			Indices[Element++] = (i * _fidelity) + ((j + 1) % _fidelity);
			Indices[Element++] = (i * _fidelity) + (j);
			Indices[Element++] = (((i + 1) % _fidelity) * _fidelity) + ((j + 1) % _fidelity);
		}
	}
	//**DEFAULT TEXTURE CREATE**\\
	//get the data for the image
	unsigned char* ImageData = stbi_load("assets/textures/jerma.jpg",
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
	//**DEFAULT TEXTURE END**\\
	
	// Create the Vertex Array and associated buffers
	GLuint VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), Indices, GL_STATIC_DRAW);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(GLfloat), Vertices, GL_STATIC_DRAW);

	// Vertex Information (Position, Texture Coords and Normals)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	//tex coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	drawType = GL_TRIANGLES;

	// Clean up the used memory
	delete[] Vertices;
	delete[] Indices;
}

CSphereRender::~CSphereRender()
{
}

//Render the sphere with the minimum reqs
void CSphereRender::Render(glm::mat4* _modelMat, glm::mat4* _PVM)
{
	glUseProgram(sphereProg);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(sphereProg, "Texture_1"), 0);
	//Model matrix application
	GLint modelMatLoc = glGetUniformLocation(sphereProg, "Model");
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(*_modelMat));

	GLint PVMMatLoc = glGetUniformLocation(sphereProg, "PVM");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(*_PVM));

	glDrawElements(drawType, indexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

//Render the sphere with a custom texture
void CSphereRender::Render(GLuint* _texture, glm::mat4* _modelMat, glm::mat4* _PVM)
{
	glUseProgram(sphereProg);
	glBindVertexArray(VAO);
	//Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *_texture);
	glUniform1i(glGetUniformLocation(sphereProg, "Texture_1"), 0);
	//Model matrix application
	GLint modelMatLoc = glGetUniformLocation(sphereProg, "Model");
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(*_modelMat));

	GLint PVMMatLoc = glGetUniformLocation(sphereProg, "PVM");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(*_PVM));

	glDrawElements(drawType, indexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
//Render the sphere with a custom shader and a custom texture
void CSphereRender::Render(GLuint* _prog, GLuint* _texture, glm::mat4* _modelMat, glm::mat4* _PVM)
{
	glUseProgram(*_prog);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *_texture);
	glUniform1i(glGetUniformLocation(*_prog, "Texture_1"), 0);
	//Model matrix application
	GLint modelMatLoc = glGetUniformLocation(*_prog, "Model");
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(*_modelMat));

	GLint PVMMatLoc = glGetUniformLocation(*_prog, "PVM");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(*_PVM));

	lights->PassPointLights(_prog);

	glDrawElements(drawType, indexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
