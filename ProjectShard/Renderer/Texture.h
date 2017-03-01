#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <iostream>
#include <vector>
#include <GL\gl3w.h>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF

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