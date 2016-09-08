#include "DebugDrawManager.h"

DebugDrawManager g_debugDrawMgr;

void DebugDrawManager::AddLine(const Vector3 &startPos, const Vector3 &endPos, Vector3 &color,
	float lineWidth, bool depthEnabled)
{
	// TODO(Darren): Error checking for max array of lines.

	lines[num].data[0] = startPos.x;		lines[num].data[1] = startPos.y;		lines[num].data[2] = startPos.z;
	lines[num].data[3] = color.x;			lines[num].data[4] = color.y;			lines[num].data[5] = color.z;
	lines[num].data[6] = endPos.x;			lines[num].data[7] = endPos.y;			lines[num].data[8] = endPos.z;
	lines[num].data[9] = color.x;			lines[num].data[10] = color.y;			lines[num].data[11] = color.z;

	num++;
	drawLines.push_back(line);
}

void DebugDrawManager::AddCross(const Vector3 &pos, Vector3 &color,
	float lineWidth, bool depthEnabled)
{

}

void DebugDrawManager::Submit(Camera &camera)
{
	// Line debug drawing.
	{
		Shader lineShader;
		lineShader.LoadShader("Shaders/DebugDrawMgr/DebugLine.vert", "Shaders/DebugDrawMgr/DebugLine.frag", "Shaders/DebugDrawMgr/DebugLine.gs");
		lineShader.Use();

		GLuint VBO, VAO;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		GLsizeiptr size = sizeof(Line) * num;
		glBufferData(GL_ARRAY_BUFFER, size, &lines, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glBindVertexArray(0);

		lineShader.Use();
		Matrix4 projection = Matrix4();
		projection = projection.perspectiveProjection(camera.zoom, 900.0f / 600.0f, 0.1f, 100.0f);
		Matrix4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(lineShader.Program, "projection"), 1, GL_FALSE, &projection.data[0]);
		glUniformMatrix4fv(glGetUniformLocation(lineShader.Program, "view"), 1, GL_FALSE, &view.data[0]);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 4);
		glBindVertexArray(0);
	}

	// All debug draw primitives have been rendered so now clear the
	// vector for new updated positions of primitves.
	num = 0;
	drawLines.clear();
}