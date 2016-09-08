#ifndef DEBUG_DRAW_MANAGER_H
#define DEBUG_DRAW_MANAGER_H

#include "Math\Vector3.h"
#include "Math\Matrix4x4.h"
#include <vector>
#include "Shader.h"
#include "Camera.h"

class DebugDrawManager
{
private:
	static const unsigned int MAX_LINES = 256;

	struct Line
	{
		GLfloat data[12];

		// NOTE(Darren): Could start implementing vec3 data now since, struct 
		// data is squential. Easier for reading and maintaining (I think).
	};	
	Line line;
	std::vector<Line> drawLines;
	Line lines[MAX_LINES];
	int num = 0;

public:
	void AddLine(const Vector3 &startPos,
				const Vector3 &endPos,
				Vector3 &color,
				float lineWidth = 1.0f,
				bool depthEnabled = true);

	void AddCross(const Vector3 &pos,
				Vector3 &color,
				float lineWidth = 1.0f,
				bool depthEnabled = true);

	// Submit the debug draw primtives for rendering.
	void Submit(Camera &camera);
};

extern DebugDrawManager g_debugDrawMgr;

#endif