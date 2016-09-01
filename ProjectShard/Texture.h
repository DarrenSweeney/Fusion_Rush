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
	Texture(const char* path);
	~Texture();

	void Bind();
};

#endif