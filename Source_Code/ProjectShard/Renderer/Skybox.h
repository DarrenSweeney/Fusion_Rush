#ifndef SKYBOX_H
#define SKYBOX_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"
#include "..\Game\Camera.h"

class Skybox
{
public:
	Skybox();
	~Skybox();
	void Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight);

private:
	Texture *skybox;
	Shader *shaderSkybox;
	GLuint skyboxVAO = 0, skyboxVBO = 0;

	void RenderSkybox();
};

#endif