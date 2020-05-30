#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLWindow.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Light.h"

const float toRadians = 3.14159265f / 180.0f;

GLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shederList;
Camera camera;

Texture brickTexture;

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shader/shader.vert";
// Fragment Shader
static const char* fShader = "Shader/shader.frag";

void calcAvgNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int verticesCount, 
					unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i+1] * vLength;
		unsigned int in2 = indices[i+2] * vLength;

		glm::vec3 v1(vertices[in1] + vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] + vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticesCount / vLength; ++i)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}

}

void CreateObjects() 
{
	unsigned int indeces[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f,	 -1.0f,		0.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f,	 -1.0f,		1.0f,	0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f,	 -1.0f,		0.0f,	1.0, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f,	 1.0f,		0.0f,	0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	calcAvgNormals(indeces, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indeces, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indeces, 32, 12);
	meshList.push_back(obj2);
} 

void createShaders() 
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shederList.push_back(*shader1);
}

int main(int argc, char** argv) 
{

	// Create Window
	mainWindow = GLWindow(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	createShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Texture/brick.png");
	brickTexture.LoadTexture();

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f,
					  2.0f, -1.0f, -2.0f, 1.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, unifromAmbientInstesity = 0, uniformAmbientColor = 0,
		uniformDirection = 0, unifromDiffuseIntesity = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// Get + Handle user input event
		glfwPollEvents();

		camera.KeyControl(mainWindow.getKeys(), deltaTime);
		camera.MouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shederList[0].UseShader();
		uniformModel = shederList[0].GetModelLocation();
		uniformProjection = shederList[0].GetProjectionLocation();
		uniformView = shederList[0].GetViewLocation();
		uniformAmbientColor = shederList[0].GetAmbientColorLocation();
		unifromAmbientInstesity = shederList[0].GetAmbientIntesityLocation();
		unifromDiffuseIntesity = shederList[0].GetDiffuseIntesityLocation();
		uniformDirection = shederList[0].GetDirectionLocation();

		mainLight.UseLight(unifromAmbientInstesity, uniformAmbientColor,
							unifromDiffuseIntesity, uniformDirection);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

