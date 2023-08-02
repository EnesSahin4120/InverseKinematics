#include <string.h>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Line.h"
#include "IKController.h"

const GLint WIDTH = 800, HEIGHT = 600;

Window mainWindow;
std::vector<Shader> objectShader;
std::vector<Line*> lines;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Camera camera;

// Object Vertex Shader 
static const char* vShader = "Shaders/object.vert";

// Object Fragment Shader
static const char* fShader = "Shaders/object.frag";

IKController *ikController = new IKController(7, 0.15f, glm::vec3(0.0f, 0.0f, 0.0f));

void CreateShader()
{
	Shader *s_Object = new Shader();
	s_Object->CreateFromFiles(vShader, fShader);
	objectShader.push_back(*s_Object);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialize();

	CreateShader();
	ikController->SetupLinks();
	camera = Camera(glm::vec3(0.0f, 0.5f, -0.75f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.1f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.5f, 50.0f);
	while (!mainWindow.GetShouldClose())
	{
		glLineWidth(1.0f);

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		glfwPollEvents();
		ikController->RootControl(mainWindow.GetKeys(), deltaTime);
		camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1.0f);

		objectShader[0].UseShader();
		uniformModel = objectShader[0].GetModelLocation();
		uniformProjection = objectShader[0].GetProjectionLocation();
		uniformView = objectShader[0].GetViewLocation();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

		ikController->UpdateLinks(lines);
		for (int i = 0; i < lines.size(); i++)
			lines[i]->RenderLine();

		glUseProgram(0);

		mainWindow.SwapBuffers();
	}
	return 0;
}