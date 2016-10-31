#include "InstancingEntity.h"

InstancingEntity::InstancingEntity()
{
	instancingShader = g_resourceMgr.GetShader(SID("Instancing"));
	instancingShader->Use();
	glUniform3f(glGetUniformLocation(instancingShader->Program, "skyColour"), 0.8f, 0.45f, 0.4f);
}

InstancingEntity::~InstancingEntity()
{
	delete instancingShader;
}

void InstancingEntity::SetUpBuffers(GLuint &vao, Matrix4 *matrices, GLuint amount)
{
	GLuint buffer;
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Matrix4), &matrices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Vertex Attributes
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)(sizeof(Vector4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)(2 * sizeof(Vector4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (GLvoid*)(3 * sizeof(Vector4)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	// Clean up
	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
}

void InstancingEntity::RenderInstance(Model *model, GLuint amount)
{
	glBindTexture(GL_TEXTURE_2D, model->texturesLoaded[0].id);
	for (GLuint i = 0; i < model->meshes.size(); i++)
	{
		glBindVertexArray(model->meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, model->meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void InstancingEntity::UseInstancingShader()
{
	instancingShader->Use();
}

GLuint InstancingEntity::ShaderProgramID()
{
	return instancingShader->Program;
}