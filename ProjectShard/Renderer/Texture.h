#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <iostream>
#include <vector>
#include <GL\gl3w.h>
#include <GL\glext.h>

class Texture
{
private:
	GLuint textureID;

public:
	Texture();

	GLuint LoadTexture(const char* path);
	void Bind();
	void UnBind();
	GLuint LoadCubeMap(std::vector<const GLchar*> faces);
	void BindCubeMap();
	void UnBindCubeMap();
	void DeleteTexture();
};

#endif