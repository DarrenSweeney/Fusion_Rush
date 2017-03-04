#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
	Init();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::Init()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::Render(Texture &texture, Shader &shader, Vector2 position,
	Vector2 size, GLfloat rotate, Vector3 color)
{
	Matrix4 modelMat = Matrix4();
	Matrix4 scale = Matrix4();
	Matrix4 trans = Matrix4();
	Matrix4 rotateMat = Matrix4();

	// Create a translation matrix
	trans = trans.translate(Vector3(position.x, position.y, 0.0f));

	modelMat = trans;
	// Translate to origin
	trans = trans.translate(Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));
	modelMat = modelMat * trans;
	// Rotate the sprite
	rotateMat = rotateMat.rotateZ(rotate);
	modelMat  = rotateMat * modelMat;
	// Translate back to orginal position
	trans = trans.translate(Vector3(-0.5f * size.x,  -0.5f * size.y, 0.0f));
	modelMat = trans * modelMat;

	// Create a scale matrix
	scale = scale.scale(Vector3(size.x, size.y, 1.0f));
	modelMat = scale * modelMat;

	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, &modelMat.data[0]);
	glUniform3f(glGetUniformLocation(shader.Program, "spriteColor"), color.x, color.y, color.z);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}