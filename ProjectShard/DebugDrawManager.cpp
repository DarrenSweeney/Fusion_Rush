#include "DebugDrawManager.h"

DebugDrawManager g_debugDrawMgr;

void DebugDrawManager::AddLine(const Vector3 &startPos, const Vector3 &endPos, Vector3 &color,
	float lineWidth, bool depthEnabled)
{
	if (lineCount >= MAX_LINES)
		return;

	lines[lineCount].startPos = startPos;
	lines[lineCount].color0 = color;
	lines[lineCount].endPos = endPos;
	lines[lineCount].color1 = color;

	lineCount++;
}

void DebugDrawManager::AddCross(const Vector3 &pos, Vector3 &color,
	float lineWidth, bool depthEnabled)
{
	if (lineCount + 3 > MAX_LINES)
		return;

	Vector3 lx_startPos(-LINE_WIDTH + pos.x, pos.y, pos.z), lx_endPos(+LINE_WIDTH + pos.x, pos.y, pos.z);
	Vector3 ly_startPos(pos.x, -LINE_WIDTH + pos.y, pos.z), ly_endPos(pos.x, +LINE_WIDTH + pos.y, pos.z);
	Vector3 lz_startPos(pos.x, pos.y, -LINE_WIDTH + pos.z), lz_endPos(pos.x, pos.y, +LINE_WIDTH + pos.z);

	AddLine(lx_startPos, lx_endPos, color);
	AddLine(ly_startPos, ly_endPos, color);
	AddLine(lz_startPos, lz_endPos, color);
}

void DebugDrawManager::Submit(Camera &camera)
{
	// Line debug drawing.
	{
		lineShader = g_resourceMgr.GetShader(SID("DebugLine"));
		lineShader->Use();

		GLuint VBO, VAO;
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		GLsizeiptr size = sizeof(Line) * lineCount;
		glBufferData(GL_ARRAY_BUFFER, size, &lines, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glBindVertexArray(0);

		Matrix4 projection = Matrix4();
		// TODO(Darren): Remove this, it's hard coded.
		projection = projection.perspectiveProjection(camera.zoom, 900.0f / 600.0f, 0.1f, 100.0f);
		Matrix4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(lineShader->Program, "projection"), 1, GL_FALSE, &projection.data[0]);
		glUniformMatrix4fv(glGetUniformLocation(lineShader->Program, "view"), 1, GL_FALSE, &view.data[0]);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 2 * lineCount);
		glBindVertexArray(0);
	}

	// All debug draw primitives have been rendered so now clear the
	// counts for new updated positions of primitves.
	lineCount = 0;
}