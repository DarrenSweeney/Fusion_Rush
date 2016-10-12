#include "Track.h"

Track::Track()
	: amount(100)
{
	
}

Track::~Track()
{
	delete raceTrack;
	delete[] modelMatrices;
}

void Track::Init()
{
	raceTrack = g_resourceMgr.GetModel(SID("RaceTrack"));
	instancingShader = g_resourceMgr.GetShader(SID("Instancing"));

	modelMatrices = new Matrix4[amount];

	// Set model matrices
	Matrix4 scaleMatrix = Matrix4();
	scaleMatrix = scaleMatrix.scale(Vector3(3.0f, 0.0f, 3.0f));
	for (GLuint i = 0; i < amount; i++)
	{
		Matrix4 model = Matrix4();
		Matrix4 transMatrix = Matrix4();

		transMatrix = transMatrix.translate(Vector3(0.0f, -4.0f, (120.0f * i)));
		modelMatrices[i] = scaleMatrix * transMatrix;
	}

	for (GLuint i = 0; i < raceTrack->meshes.size(); i++)
		SetUpBuffers(raceTrack->meshes[i].VAO, modelMatrices);
}

void Track::SetUpBuffers(GLuint &vao, Matrix4 *matrices)
{
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Matrix4), &modelMatrices[0], GL_STATIC_DRAW);
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

void Track::Render(Camera &camera, GLsizei screenWidth, GLsizei screenHeight)
{
	Matrix4 projection = Matrix4();
	projection = projection.perspectiveProjection(camera.zoom, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);
	Matrix4 view;
	view = camera.GetViewMatrix();

	instancingShader->Use();
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
	glUniformMatrix4fv(glGetUniformLocation(instancingShader->Program, "view"), 1, GL_FALSE, &view.data[0]);

	// Render the layer of tracks
	glBindTexture(GL_TEXTURE_2D, raceTrack->texturesLoaded[0].id);
	for (GLuint i = 0; i < raceTrack->meshes.size(); i++)
	{
		glBindVertexArray(raceTrack->meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, raceTrack->meshes[i].vertices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}