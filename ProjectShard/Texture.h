#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <iostream>
#include <GL\gl3w.h>
#include <GL\glext.h>

class Texture
{
private:
	GLuint textureID;

public:
	Texture();
	~Texture();

	GLuint LoadTexture(const char* path);
	void Bind();
	void UnBind();
};

#endif