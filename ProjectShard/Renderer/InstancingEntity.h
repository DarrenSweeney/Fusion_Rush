#ifndef INSTANCING_ENTITY_H
#define INSTANCING_ENTITY_H

#include "..\Core\ResourceManager.h"
#include "..\Math\Matrix4x4.h"

class InstancingEntity
{
public:
	InstancingEntity();
	~InstancingEntity();
	GLuint amount;

protected:
	void SetUpBuffers(GLuint &vao, Matrix4 *matrices, GLuint amount);
	void RenderInstance(Model *model, GLuint amount);
	void UseInstancingShader();
	GLuint ShaderProgramID();

private:
	Shader *instancingShader;
};

#endif