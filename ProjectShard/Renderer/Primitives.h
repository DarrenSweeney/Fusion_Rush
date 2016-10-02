#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <GL\gl3w.h>

class Primitives
{
public:
	Primitives();
	~Primitives();

	void RenderQuad();
	void RenderCube();

private:
	GLuint quadVAO, quadVBO;
	GLuint cubeVAO, cubeVBO;
};

#endif