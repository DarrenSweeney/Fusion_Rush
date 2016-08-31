#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL\gl3w.h>

class Shader
{
public:
	// The shader program ID
	GLuint Program;
	void Use();

	Shader LoadShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath = NULL);

private:
	void Compile(const GLchar *vShaderCode, const GLchar *fShaderCode, const GLchar *gShaderCode = NULL);
};

#endif