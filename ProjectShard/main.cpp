#include <iostream>
#include "Shader.h"
#include <GL\gl3w.h>
#include <GLFW\glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLuint quadVAO = 0, quadVBO = 0;
void RenderQuad();

int main(int argc, char* argv[])
{
	std::cout << "DARREN_SWEENEY::Project Shard..." << std::endl;

	if (!glfwInit())
	{
		printf("Failed to inialize opengl");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(640, 480, "Project Shard", NULL, NULL);
	glfwSetKeyCallback(window, key_callback);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit())
	{
		printf("Failed to inialize opengl");
		return -1;
	}

	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader shader = shader.LoadShader("test.vert", "test.frag");

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		RenderQuad();

		glfwSwapBuffers(window);
	}

	// De-allocate all resources
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void RenderQuad()
{
	if (quadVAO == 0)
	{
		GLfloat quadVertices[] = {
			// Positions			// Texture Coords
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		};

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}